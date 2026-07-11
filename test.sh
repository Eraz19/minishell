foo()
{
	echo "foo"
	unset -f foo
	echo "after"
	foo
	echo "end"
}

foo
