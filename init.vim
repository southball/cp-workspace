" Select region and then type :Hash to hash your selection.
" Useful for verifying that there aren't mistypes.
ca Hash w !cpp -dD -P -fpreprocessed \| tr -d '[:space:]' \
  \| md5sum \| cut -c-6

nnoremap <F9> :execute '!./clip ' . expand('%:t:r')<CR>

" Disable ALE for C++ temporarily.
autocmd BufNew,BufEnter *.cpp execute "silent! ALEDisableBuffer"

" Load original .vimrc
source ~/.config/nvim/init.vim

" Commands for workspace.
command Reset %! cat < template.cpp
