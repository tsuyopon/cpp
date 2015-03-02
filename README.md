
[MEMO]
if you would like to convert into utf8. type this command.
	$ find . -type f -print0 | xargs -0 nkf --overwrite -w -Lu
