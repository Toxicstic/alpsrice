-- shorthand
function map(mode, shortcut, command)
  vim.api.nvim_set_keymap(mode, shortcut, command, { noremap = true, silent = true })
end

function nmap(shortcut, command)
  map('n', shortcut, command)
end

function imap(shortcut, command)
  map('i', shortcut, command)
end

-- keymapping
vim.g.mapleader = ";"

--- escape terminal mode with esc
map("t","<Esc>","<C-\\><C-n>")

--- tabs
local tableader=" "
nmap(string.format("%ste",tableader),":tabe<CR>:Exp<CR>")
nmap(string.format("%stt",tableader),":tabe<CR>:terminal<CR>")
nmap(string.format("%se",tableader),":Exp<CR>")
nmap(string.format("%sl",tableader),":tabn<CR>")
nmap(string.format("%sh",tableader),":tabp<CR>")

--- quicker closing
nmap("zz",":wq<CR>")
nmap("zq",":q<CR>")
nmap("zA",":wqa<CR>")

--- splits
nmap("<leader>sv",":vsplit<CR><C-W><C-W>:Exp<CR>")
nmap("<leader>sh",":split<CR><C-W><C-W>:Exp<CR>")

---- resizing
nmap('<leader>h', '2<C-w><')
nmap('<leader>l', '2<C-w>>')
nmap('<leader>k', '2<C-w>+')
nmap('<leader>j', '2<C-w>-')

---- movement
nmap("sh","<C-W>h")
nmap("sj","<C-W>j")
nmap("sk","<C-W>k")
nmap("sl","<C-W>l")

nmap("<leader>e",":Exp<CR>")
