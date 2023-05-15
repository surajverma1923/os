echo "Executable files in the current directory: "
	for file in *
		do
			if[ -x "$file" ]
					echo "$file"
		done
