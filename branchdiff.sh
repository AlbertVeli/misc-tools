#!/bin/sh

# Use case: simple fork
#
# Show difference between current branch and
# the fork point on the parent branch.
#
# Example, 4.28.x-bugfix is checked out:
#
# o---o---1---o---o---o     4.28.x
#          \
#           o---o---o       4.28.x-bugfix
#
# Run
#
# branchdiff.sh 4.28.x
#
# to show changes on the 4.28.x-bugfix branch.
# This script finds the commit hash of commit 1 in
# the picture and runs git diff <id of commit 1>.

usage()
{
	echo "Error: $1"
	echo ""
	echo "Usage: $(basename $0) <fork branch>"
	echo ""
	echo "Shows git diff between current branch and"
	echo "fork point on given fork branch"
	exit 1
}

if ! $(git rev-parse --is-inside-work-tree > /dev/null 2>&1); then
	usage "Not inside a git work tree"
fi

fork_branch=$1
if test -z "$fork_branch"; then
	usage "No parent branch name given"
fi

fork_commit=$(git merge-base --fork-point $fork_branch) || \
	usage "Couldn't find fork point on branch $fork_branch"

git diff $fork_commit
