" Select region and then type :Hash to hash your selection.
" Useful for verifying that there aren't mistypes.
ca Hash w !cpp -dD -P -fpreprocessed \| tr -d '[:space:]' \
  \| md5sum \| cut -c-6

nnoremap <F9> :execute '!./clip ' . expand('%:t:r')<CR>
nnoremap <F10> :execute 'vsplit \| term ./run ' . expand('%:t:r')<CR>i

" Load original .vimrc
source ~/.config/nvim/init.vim

" Commands for workspace.
command! Reset %! cat < template.cpp
