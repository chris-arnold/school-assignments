#!/bin/tcsh

if ( ! -d backup ) then
	echo "Would you like to create backup directory?"
	set input=$<
	switch ($input)
		case [yY]:
		case [yY][eE][sS]:
			mkdir backup
			if ( ! -d backup ) then
				echo ERROR CREATING BACKUP DIRECTORY
				exit1
			endif
			breaksw
		case [nN]:
		case [nN][oO]:
			echo "No backup directory created."
			exit 1
			breaksw
		default:
			echo "Invalid input"
			exit 1
			breaksw
	endsw

endif

set dest=`pwd`/backup

foreach i ( *.c )
	if ( ! -f "$dest/$i" ) then
		echo Backing up $i
		cp "$i" "$dest/$i"
	endif

	if ( -M "$i" > -M "backup/$i" ) then
		echo Backup version of $i is old...
		cp -f "$i" "$dest/$i"

	endif
	
	if ( `cmp -s "$i" "backup/$i"` ) then
		echo Files differ. Overwriting differences.
		cp -f "$i" "$dest/$i"
	endif

end

echo BACKUP COMPLETE!


	
