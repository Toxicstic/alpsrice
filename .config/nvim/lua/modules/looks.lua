local o = vim.o
o.termguicolors=true
o.smd=false
-- o.nowrap=true
-- o.shiftwidth=4
-- o.softtabstop=4
-- o.tabstop=4
-- o.foldmethod=4
vim.g['netrw_browse_split'] = "0"

vim.cmd [[colorscheme moonfly]]

vim.cmd [[highlight Normal ctermbg=none]]
vim.cmd [[highlight NonText ctermbg=none]]
vim.cmd [[highlight Normal guibg=none]]
vim.cmd [[highlight NonText guibg=none]]
