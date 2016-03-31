export PATH=$PATH:/Users/mam/bin/apache-maven-3.3.9/bin
export PATH=$PATH:/Users/mam/bin/gradle-2.11/bin
export P4CONFIG=.p4config

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

