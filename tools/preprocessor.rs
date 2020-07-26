use std::path::Path;
use std::collections::HashSet;

fn get_include(line: &str) -> Option<&str> {
    let line = line.trim();
    if let Some(line) = line.strip_prefix("#include \"") {
        if let Some(line) = line.strip_suffix("\"") {
            Some(line)
        } else {
            None
        }
    } else {
        None
    }
}

fn process(filename: &Path, template_folder: &Path, included_paths: &mut HashSet<String>) -> Option<Vec<String>> {
    let is_template = filename.starts_with(template_folder);
    eprintln!("Processing file: {:?} (template: {:?})", filename, is_template);

    if let Ok(content) = std::fs::read_to_string(filename) {
        content
            .split('\n')
            .filter(|line: &&str| !is_template || line.trim().len() > 0)
            .map(|line: &str| {
                let line = line.to_owned();
                if let Some(template_name) = get_include(&line) {
                    let template_path = filename
                        .parent()
                        .expect("Cannot find parent directory of template file.")
                        .join(template_name);
                    
                    // For handling includes like "bits/stdc++.h"
                    if !template_path.exists() {
                        eprintln!("{:?}: skipped processing {}", filename, line);
                        return vec![line];
                    }

                    let full_path = template_path
                        .canonicalize()
                        .expect("Failed to resolve path for file.")
                        .to_str()
                        .expect("Failed to turn path to string.")
                        .to_owned();

                    if included_paths.contains(&full_path) {
                        eprintln!("{:?}: \"{}\" is already included", filename, template_name);
                        vec![]
                    } else if template_path.starts_with(template_folder) {
                        included_paths.insert(full_path);
                        process(&template_path, template_folder, included_paths)
                            .unwrap_or(vec![line])
                    } else {
                        vec![line]
                    }
                } else {
                    vec![line]
                }
            })
            .map(|lines: Vec<String>| lines.join("\n"))
            .collect::<Vec<String>>()
            .into()
    } else {
        None
    }
}

fn main() {
    let args: Vec<String> = std::env::args().into_iter().collect();
    assert!(args.len() >= 2, "The file name must be provided.");

    eprintln!("Current working directory: {:?}", std::env::current_dir());

    let source = args[1].clone();
    let filename = Path::new(&source);
    let template_folder = filename
        .parent()
        .expect("Failed to find parent directory of source file.")
        .join("template");
    let mut included_paths: HashSet<String> = HashSet::new();
    let result = process(&filename, &template_folder, &mut included_paths)
        .expect("Failed to process code.")
        .join("\n");

    println!("{}", result);
}
