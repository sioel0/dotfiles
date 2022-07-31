# env variable
export EDITOR="nvim"
export VISUAL="nvim"
export PAGER="less"
export PROJECTS="~/gits"
export PATH="$PATH:/home/sioel0/.bin:/home/sioel0/.local/bin:/home/sioel0/.scripts"
export TERM="screen-256color"
# aliases
alias cat='bat'
alias gdb='gdb -q'
alias ls='ls --color=auto'
alias ll='ls -l'
alias la='ls -la'
alias sv='sudo nvim'
alias sctl='sudo systemctl'
alias ssh='ssh -X'
alias p='sudo pacman'
alias v='nvim'

# git aliases
alias ga='git add'
alias gs='git status'
alias gc='git commit -m'
alias gps='git push origin'
alias gf='git fetch'
alias gpl='git pull origin'

# start starship prompt
eval "$(starship init bash)"
eval "$(zoxide init bash)"
