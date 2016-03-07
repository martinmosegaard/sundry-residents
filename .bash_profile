export PATH=$PATH:/Users/mam/bin/apache-maven-3.3.9/bin
export PATH=$PATH:/Users/mam/bin/gradle-2.11/bin
export P4CONFIG=.p4config

# Set the title of an iTerm tab.
# Usage: title my project.
function title {
  # Obscure syntax to set the title of an iTerm tab.
  # $* means the arguments to title, e.g. 'my project' above.
  echo -ne "\033]0;"$*"\007"
}

alias ll='ls -GlAhp'
alias ls='ls -G'
alias dm='eval $(docker-machine env default)'

