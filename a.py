from multiprocessing import Pool
import os

TEST_ID = 1

def run_command(path):
	os.system(f"./communicate_client localhost < ./test/test{TEST_ID}/client{path}.txt > out/test{TEST_ID}/output{path}.txt &")

paths = [1, 3, 2]
pool = Pool()
pool.map(run_command, paths)