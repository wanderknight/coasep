test:
	gcc veri_loop_unrolling.c -o veri_loop_unrolling
	echo "********start to run veri_loop_unrolling.exe******"
	veri_loop_unrolling.exe
	echo "********end to run veri_loop_unrolling.exe******"

all:
	gcc veri_loop_unrolling.c -o veri_loop_unrolling
	echo "********start to run veri_loop_unrolling.exe******"
	veri_loop_unrolling.exe
	echo "********end to run veri_loop_unrolling.exe******"

	gcc veri_loop_unrolling.c -O3 -o veri_loop_unrolling
	echo "********start to run veri_loop_unrolling.exe******"
	veri_loop_unrolling.exe
	echo "********end to run veri_loop_unrolling.exe******"

	gcc veri_Branch_prediction.c -o veri_Branch_prediction
	echo "********start to run veri_Branch_prediction.exe******"
	veri_Branch_prediction.exe
	echo "********end to run veri_Branch_prediction.exe******"

	gcc design_Branch_prediction.c -o design_Branch_prediction
	echo "********start to run design_Branch_prediction.exe******"
	design_Branch_prediction.exe
	echo "********end to run design_Branch_prediction.exe******"

clean:
	del -f *.exe
