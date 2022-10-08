# Setup a red prompt for root and a green one for users.
# Symlink this file to color_prompt.sh to actually enable it.

_file=$'\e[34m'
_normal=$'\e[0m'
if [ "$USER" = root ]; then
	_color=$'\e[1;31m'
	_symbol='#'
else
	_color=$'\e[1;32m'
	_symbol='$'
fi
PS1="\[$_color\]\u@\h\[$_normal\]:\[$_file\]\w\[$_normal\]$_symbol \[$_normal\]"
unset _normal _color _symbol
