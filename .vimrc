" KACTL options
set cin aw ai is ts=4 sw=4 tm=50 nu noeb bg=dark ru cul
sy on   |   im jk <esc>   |   im kj <esc>   |   no ; :
" Select region and then type :Hash to hash your selection.
" Useful for verifying that there aren't mistypes.
ca Hash w !cpp -dD -P -fpreprocessed \| tr -d '[:space:]' \
  \| md5sum \| cut -c-6

" Custom options
set mouse=a autoread
nnoremap <F12> :!cat % \| clip.exe<CR><CR>

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

" MiniBufExpl settings
let g:miniBufExplModSelTarget = 1
let g:miniBufExplUseSingleClick = 1
nnoremap	<C-right>	:MBEbn<CR>
nnoremap	<C-left>	:MBEbp<CR>
set runtimepath^=~/.vim/bundle/minibufexpl.vim
