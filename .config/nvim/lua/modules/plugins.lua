local Plug = vim.fn['plug#']

vim.call('plug#begin', '~/.config/nvim/plugged')

-- colorscheme
Plug 'bluz71/vim-moonfly-colors'

-- Language support
Plug 'lervag/vimtex'

-- interface
Plug 'nvim-lualine/lualine.nvim'
Plug 'kyazdani42/nvim-web-devicons'
Plug 'akinsho/bufferline.nvim'

vim.call('plug#end')

vim.cmd [[ let g:vimtex_view_method = 'mupdf' ]]
