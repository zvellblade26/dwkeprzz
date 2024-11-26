#!/usr/bin/env bash
user=$(whoami)
eval "$(zoxide init bash)"
function _zq() {
  if [ -n "$1" ]; then
    z "$1" && ls
  else
    z ~ && ls
  fi
}
alias z='_zq'
alias zi='function _zz(){ zi "$1" && ls; }; _zz'

export PATH=$PATH:"/home/$user/.local/bin"
iatest=$(expr index "$-" i)
if [[ $iatest -gt 0 ]]; then bind "set completion-ignore-case on"; fi
if [[ $iatest -gt 0 ]]; then bind "set show-all-if-ambiguous On"; fi

export EDITOR=nvim
export VISUAL=nvim

alias sureset="faillock --user $user --reset"
alias smci="faillock --user $user --reset && sudo make clean install"
alias sudo="faillock --user $user --reset && sudo $@"
alias smcu="faillock --user $user --reset && sudo make clean uninstall"
alias feh="feh -d -S filename '$1'"
alias grep="grep --color=auto"
alias paci="sudo pacman -S"
alias pac="sudo pacman"
alias v="nvim"
alias vv="faillock --user $user --reset && sudoedit"
alias gc="git clone"
alias ebrc="v ~/.bashrc"
alias einitrc="v ~/.xinitrc"
alias mtpfs="simple-mtpfs --device 1 ~/SamsungGalaxyA50/ && cd ~/SamsungGalaxyA50"
alias da='date "+%Y-%m-%d %A %T %Z"'

alias cp='cp -rv'
alias scp='sudo cp -rv'
alias rm='rm -rv'
alias srm='sudo rm -rv'
alias mv='mv -v'
alias smv='sudo mv -v'
alias mdir='mkdir -p'
alias smdir='sudo mkdir -p'
alias ps='ps auxf'
alias ..="cd .."
alias ...="cd ../.."
alias ....="cd ../../.."

alias ls='ls -aFh --color=always' # add colors and file type extensions
alias la="ls -Alh"                # show hidden files
alias ls="ls -aFh --color=always" # add colors and file type extensions
alias lx="ls -lXBh"               # sort by extension
alias lk="ls -lSrh"               # sort by size
alias lc="ls -ltcrh"              # sort by change time
alias lu="ls -lturh"              # sort by access time
alias lr="ls -lRh"                # recursive ls
alias lt="ls -ltrh"               # sort by date
alias lm="ls -alh |more"          # pipe through 'more'
alias lw="ls -xAh"                # wide listing format
alias ll="ls -Fls"                # long listing format
alias labc='ls -lap'              # alphabetical sort
alias lf="ls -l | egrep -v '^d'"  # files only
alias ldir="ls -l | egrep '^d'"   # directories only
alias lla='ls -Al'                # List and Hidden Files
alias las='ls -A'                 # Hidden Files
alias lls='ls -l'                 # List

alias mx='chmod +x'

extract() {
	for archive in "$@"; do
		if [ -f "$archive" ]; then
			case $archive in
			*.tar.bz2) tar xvjf $archive ;;
			*.tar.gz) tar xvzf $archive ;;
			*.bz2) bunzip2 $archive ;;
			*.rar) rar x $archive ;;
			*.gz) gunzip $archive ;;
			*.tar) tar xvf $archive ;;
			*.tbz2) tar xvjf $archive ;;
			*.tgz) tar xvzf $archive ;;
			*.zip) unzip $archive ;;
			*.Z) uncompress $archive ;;
			*.7z) 7z x $archive ;;
			*) echo "don't know how to extract '$archive'..." ;;
			esac
		else
			echo "'$archive' is not a valid file!"
		fi
	done
}
export LESS_TERMCAP_mb=$'\E[01;31m'
export LESS_TERMCAP_md=$'\E[01;31m'
export LESS_TERMCAP_me=$'\E[0m'
export LESS_TERMCAP_se=$'\E[0m'
export LESS_TERMCAP_so=$'\E[01;44;33m'
export LESS_TERMCAP_ue=$'\E[0m'
export LESS_TERMCAP_us=$'\E[01;32m'
PS1='\[$(tput setaf 33)\]\w \[$(tput setaf 69)\]\[$(tput setaf 105)\]  \[$(tput setaf 148)\]'
#        
zz() {
	z	"$(find "/home/$user/" -type d \( -name "DATA:D" -or -name "DATA:C" \) -prune -o -type d -print | fzf)"
}
