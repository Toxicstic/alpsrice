# Append "$1" to $PATH when not already in.
# Copied from Arch Linux, see #12803 for details.
append_path () {
	case ":$PATH:" in
		*:"$1":*)
			;;
		*)
			PATH="${PATH:+$PATH:}$1"
			;;
	esac
}

append_path "/usr/local/sbin"
append_path "/usr/local/bin"
append_path "/usr/sbin"
append_path "/usr/bin"
append_path "/sbin"
append_path "/bin"
append_path "$HOME/.local/bin/"
append_path "$HOME/.local/bin/statusbar/"

unset -f append_path

export PATH
export PAGER=less
export HISTFILE=~/.local/share/hist/shell
export LESSHISTFILE=~/.local/share/hist/less

umask 022

[ $(tty | sed 's@/dev/tty@@') -eq 1 ] && startx || echo 'pts'
