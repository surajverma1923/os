sum=0
read -p "Enter a num: " n

for ((i=1;i<=n;i+=2))
do
	sum=$((sum+i))
done
echo "The sum of odd numbers is: $sum"
