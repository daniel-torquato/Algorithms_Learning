new:
	Scripts/create.bash

project:
	@read -p "Project Language: " lang; \
	read -p "project name: " name; \
	cp -rn Templates/$$lang Projects/$$name;

interview:
	@read -p "Project Language: " lang; \
	read -p "project name: " name; \
	cp -rn Templates/$$lang C/$$name;
