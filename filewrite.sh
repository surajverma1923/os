filename="sum.sh"
if [-w "$filename"]
then 
	echo "Write permission is already enabled for $filename"
else
	echo "Adding write permission to $filename ..."
	chmod +w "$filename"
	echo "Write permission is added for $filename"
fi
