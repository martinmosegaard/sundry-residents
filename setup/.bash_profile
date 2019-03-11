export PATH=$PATH:/Users/mam/bin/apache-maven-3.3.9/bin
export PATH=$PATH:/Users/mam/bin/gradle-3.0/bin
export P4CONFIG=.p4config
export GROOVY_HOME=/usr/local/opt/groovy/libexec

# Working directory, colors and git branch name
# Prerequisite: brew install git bash-completion
# See also: https://gist.github.com/trey/2722934
source /usr/local/git/contrib/completion/git-prompt.sh # to define __git_ps1
export PS1="\[\033[36m\]\w\[\033[33;1m\]\$(__git_ps1)\[\033[m\] \$ "

# http://osxdaily.com/2012/02/21/add-color-to-the-terminal-in-mac-os-x/
export CLICOLOR=1
export LSCOLORS=GxFxCxDxBxegedabagaced

# Create the GitHub labels used in the pragmatic workflow.
# http://www.praqma.com/stories/a-pragmatic-workflow/
function ghilabels {
  # First, delete the default labels
  ghi label -l | sed "s/\'/\\\'/g" | xargs -I %lb sh -c 'ghi label -D "%lb"'

  ghi label "Action - awaiting feed-back" -c 6EB82C
  ghi label "Action - needs grooming"     -c 009800
  ghi label "Prio 1 - must have"          -c E83D0F
  ghi label "Prio 2 - should have"        -c EB6420
  ghi label "Prio 3 - could have"         -c E8850F
  ghi label "Prio 4 - won't have"         -c E8A80F
  ghi label "Size 0 - Briefing"           -c C7DEF8
  ghi label "Size 1 - small"              -c 20B4E5
  ghi label "Size 2 - medium"             -c 208FE5
  ghi label "Size 3 - large"              -c 0052CC
  ghi label "Size 4 - too big"            -c 100B6B
  ghi label "Status - duplicate"          -c 111111
  ghi label "Status - workable"           -c EDEDED
  ghi label "Status - in progress"        -c EDEDED
  ghi label "Status - up Next"            -c EEEEEE
}

# Extract a tar file into its own directory
# regardless of how it was created.
function tarx {
  # See if the archive files have a common root folder
  local folder_count=$(tar tvf $1 | awk '{print $9}' | cut -d "/" -f 1 | uniq | wc -l)
  if [ $folder_count -eq 1 ]
  then
    echo Folder count is 1, so the archive is extracted here...
    tar xzvf $1
  else
    local folder=$1-extracted
    mkdir -p $folder
    echo Folder count is not 1, but $folder_count, so the archive is extracted into the folder $folder
    tar xzvf $1 -C $folder
  fi
}

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
