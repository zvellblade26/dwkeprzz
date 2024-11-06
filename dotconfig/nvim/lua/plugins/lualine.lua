return {
	"nvim-lualine/lualine.nvim",
	enabled = true,
	lazy = false,
	dependencies = { "nvim-tree/nvim-web-devicons", lazy = true },
	event = "VeryLazy",
	config = function()
		require("lualine").setup ({
			options = {
				--theme = "auto"
				--theme = "horizon"
				--theme = "fluoromachine"
				--theme = "dracula"
				--theme = "gruvbox_dark"
				--theme = "solarized_dark"
				--theme = "gruvbox_light"
				theme = "16color"
			},
		})
	end
}
