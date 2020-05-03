" KACTL options
set cin aw ai is ts=4 sw=4 tm=50 nu noeb bg=dark ru cul
sy on   |   im jk <esc>   |   im kj <esc>   |   no ; :
" Select region and then type :Hash to hash your selection.
" Useful for verifying that there aren't mistypes.
ca Hash w !cpp -dD -P -fpreprocessed \| tr -d '[:space:]' \
  \| md5sum \| cut -c-6

" Custom options
set autoread
set mouse=a

nnoremap <C-Left> :tabprev<CR>
nnoremap <C-Right> :tabnext<CR>
nnoremap <F5> :exec Run()<CR>
nnoremap <F6> :exec RunInteractive()<CR>
nnoremap <F7> :exec OpenRes()<CR>
nnoremap <C-F7> :exec CloseRes()<CR>
nnoremap <C-F10> :exec Reset()<CR><CR>
nnoremap <C-F11> :exec ResetWorkspace()<CR><CR>
nnoremap <F12> :!cat % \| clip.exe<CR><CR>

function Run()
	let file = expand('%:t:r')
	let extension = expand('%:e')

	if extension !=? "cpp"
		echo "The current tab is not a .cpp file."
		return
	endif

	execute "!./scripts/run.sh" file
endfunction

function RunInteractive()
	let file = expand('%:t:r')
	let extension = expand('%:e')

	if extension !=? "cpp"
		echo "The current tab is not a .cpp file."
		return
	endif

	execute "!./scripts/run_interactive.sh" file
endfunction

function OpenRes()
	let file = expand('%:t:r')
	let extension = expand('%:e')

	if extension !=? "cpp"
		echo "The current tab is not a .cpp file."
		return
	endif

	let orgtab = tabpagenr()

	execute "tabedit res/" . file . ".in"
	execute "tabedit res/" . file . ".out"
	execute "tabedit res/" . file . ".ans"
	execute "tabedit res/" . file . ".log"

	execute "tabn" orgtab
endfunction

function CloseRes()
	let file = expand('%:t:r')
	let extension = expand('%:e')

	if extension !=? "cpp"
		echo "The current tab is not a .cpp file."
		return
	endif

	let tabs = tabpagenr("$")
	let patterns = ["res/" . file . ".in", "res/" . file . ".out", "res/" . file . ".ans", "res/" . file . ".log"]

	for i in range(tabs, 1, -1)
		let buf = bufname(tabpagebuflist(i)[0])
		for pat in patterns
			if buf =~ pat
				execute "tabclose" i
			endif
		endfor
	endfor
endfunction

function Reset()
	let file = expand('%:t:r')
	let extension = expand('%:e')

	if extension !=? "cpp"
		echo "The current tab is not a .cpp file."
		return
	endif

	execute "!./scripts/reset.sh" file
endfunction

function ResetWorkspace()
	execute "!./scripts/reset_workspace.sh"
endfunction

" Ctrl-P settings
let g:ctrlp_map = '<c-p>'
let g:ctrlp_cmd = 'CtrlP'
let g:ctrlp_working_path_mode = 'ra'

" set files to open in new tab automatically
let g:ctrlp_prompt_mappings = {
	\ 'AcceptSelection("e")': ['<2-LeftMouse>'],
	\ 'AcceptSelection("t")': ['<cr>'],
	\ }

set runtimepath^=~/.vim/bundle/ctrlp.vim
