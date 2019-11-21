#!/bin/bash
###############################################################################
# Simple Script to create a project using a template
###############################################################################

echo "Project kind: "
echo "1) Interview Questions."
echo "2) Specific Language Problems."
echo "4) Data Structure Implementation."
read -p "choose: " kind;

case $kind in
	1)
		read -p "name: " name;
		read -p "Language: " lang;
		path='InterviewQuestions/'"$name"
		mkdir -p "$path"
		cp -r "Templates/$lang" "$path/"
		vim "$path/README.md"
		;;
	2)
		echo mkdir -p ProblemsByLanguage/"\"$name\""
		;;
	*)
		echo "wrong project kind or name";
esac
