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
nnoremap <F7> :exec OpenRes()<CR><CR>
nnoremap <C-F11> :exec Reset()<CR><CR>
nnoremap <F12> :!cat % \| clip.exe<CR><CR>

function Run()
	let file = expand('%:t:r')
	let extension = expand('%:e')

	if extension !=? "cpp"
		echo "The current tab is not a .cpp file."
		return
	endif

	execute "!./run.sh" file
endfunction

function RunInteractive()
	let file = expand('%:t:r')
	let extension = expand('%:e')

	if extension !=? "cpp"
		echo "The current tab is not a .cpp file."
		return
	endif

	execute "!./run_interactive.sh" file
endfunction

function OpenRes()
	let file = expand('%:t:r')
	let extension = expand('%:e')

	if extension !=? "cpp"
		echo "The current tab is not a .cpp file."
		return
	endif
	
	execute "tabedit res/" . file . ".in"
	execute "tabedit res/" . file . ".out"
	execute "tabedit res/" . file . ".ans"
	execute "tabedit res/" . file . ".log"
endfunction

function Reset()
	let file = expand('%:t:r')
	let extension = expand('%:e')

	if extension !=? "cpp"
		echo "The current tab is not a .cpp file."
		return
	endif

	execute "!./reset.sh" file
endfunction

" Ctrl-P settings

