teset:
	gcc ref_code.c -o ref_code
	echo "********start to run ref_code.exe******"
	ref_code.exe
	echo "********end to run ref_code.exe******"

all:
	gcc design_code.c -o design_code
	echo "********start to run design_code.exe******"
	design_code.exe
	echo "********end to run design_code.exe******"

	gcc float.c -o float
	echo "********start to run float.exe******"
	float.exe
	echo "********end to run float.exe******"

	gcc overflow.c -o overflow
	echo "********start to run overflow.exe******"
	overflow.exe
	echo "********end to run overflow.exe******"

	gcc odd_check.c -o odd_check
	echo "********«Î ÷∂Ø÷¥–– odd_check.exe******"

clean:
	del -f *.exe
