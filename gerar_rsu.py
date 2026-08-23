index = 0

for y in range(14000, 22001, 300):
    for x in range(6000, 15001, 300):
        print(f"*.rsu[{index}].mobility.x = {x}")
        print(f"*.rsu[{index}].mobility.y = {y}")
        print(f"*.rsu[{index}].mobility.z = 3\n")
        index += 1

print(f"# Total de RSUs: {index}")

