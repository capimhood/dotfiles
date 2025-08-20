# ~/.bashrc
# If not running interactively, don't do anything
[[ $- != *i* ]] && return

alias l='ls --color=auto'
alias la='ls -a --color=auto'
alias ll='ls -lh --color=auto '
alias lal='ls -lha --color=auto '
alias cl='clear'
alias e='hx'
alias rm='rm -i'
alias mv='mv -i'
alias cp='cp -i'
alias esrc='cd ~/.local/src/'
alias ebin='cd ~/.local/bin/'
# alias search='xbps-query -Rs "" | sort -u | grep -v "*" | fzf --preview-window="bottom:45%:wrap" --preview "xbps-query -Rv {2}"' 
alias grep='grep --color'
alias see='swayimg'

set -o vi

export PATH=$HOME/.local/bin/:$PATH

export EDITOR='vim'
export VISUAL='vim'
export MOZ_ENABLE_WAYLAND=1
export MOZ_DBUS_REMOTE=1
# export CLUTTER_BACKEND=wayland
# export XDG_SESSION_TYPE=wayland
export XDG_CURRENT_DESKTOP=sway
export QT_QPA_PLATFORM=wayland
export RTC_USE_PIPEWIRE=true
export XCURSOR_THEME=Adwaita
# export SDL_VIDEODRIVER=x11
export SDL_VIDEODRIVER=wayland

export PS1="\[$(tput setaf 6)\]\[$(tput bold)\] \$$(tput setaf 1)\] \[$(tput setaf 5)\]\W $(tput sgr0)\]"

export LESS_TERMCAP_mb=$'\e[1;32m'
export LESS_TERMCAP_md=$'\e[1;32m'
export LESS_TERMCAP_me=$'\e[0m'
export LESS_TERMCAP_se=$'\e[0m'
export LESS_TERMCAP_so=$'\e[1;4;35m'
export LESS_TERMCAP_ue=$'\e[0m'
export LESS_TERMCAP_us=$'\e[1;31m'
# export LESS='-R --use-color -Dd+r$Du+b$'
