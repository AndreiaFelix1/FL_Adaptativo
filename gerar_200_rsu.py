import math

# limites da área
xmin, xmax = 6000, 15000
ymin, ymax = 14000, 22000

total_rsu = 200

# calcular tamanho do grid
n = math.ceil(math.sqrt(total_rsu))

# calcular espaçamento automático
step_x = (xmax - xmin) / (n - 1)
step_y = (ymax - ymin) / (n - 1)

index = 0

for iy in range(n):
    for ix in range(n):

        if index >= total_rsu:
            break

        x = xmin + ix * step_x
        y = ymin + iy * step_y

        print(f"*.rsu[{index}].mobility.x = {int(x)}")
        print(f"*.rsu[{index}].mobility.y = {int(y)}")
        print(f"*.rsu[{index}].mobility.z = 3\n")

        index += 1

    if index >= total_rsu:
        break

print(f"# Total de RSUs: {index}")
