import idaapi
import idc
import json
import random

# 定义一个空列表，用于存储所有基本块的信息
basic_blocks_info = []
# 定义两个字典，用于存储已经使用的name和block
used_names = {}
used_blocks = {}

# 遍历二进制文件中的所有函数
for function_ea in Functions():
    # 获取函数对象
    function = idaapi.get_func(function_ea)
    function_name = idc.get_func_name(function.start_ea)
    print(function_name)

    # 创建函数的ACFG
    acfg = idaapi.FlowChart(function)
    # 遍历每个基本块
    for block in acfg:
        # 获取基本块的名称
        block_name = idc.get_func_name(block.start_ea)
        # 创建一个字典来存储基本块的详细信息
        block_info = {
            "name": hex(block.start_ea),
            "x": random.randint(0, 1000),  # 使用随机坐标
            "y": random.randint(0, 1000),  # 使用随机坐标
            "block": block_name,
            "assemblyCode": "",
            "successors": []
        }

        # 检查name是否已经存在，如果存在，则设置为空字符串
        if block_info["name"] in used_names:
            block_info["name"] = ""
        else:
            used_names[block_info["name"]] = True

        # 检查block是否已经存在，如果存在，则设置为空字符串
        if block_info["block"] in used_blocks:
            block_info["block"] = ""
        else:
            used_blocks[block_info["block"]] = True

        # 获取基本块的指令信息
        for head in Heads(block.start_ea, block.end_ea):
            disasm_line = idc.GetDisasm(head)
            block_info["assemblyCode"] += disasm_line + "\n"

        # 获取当前基本块的后继基本块
        successors = [hex(succ.start_ea) for succ in block.succs()]
        block_info["successors"] = successors

        # 将基本块信息添加到列表中
        basic_blocks_info.append(block_info)

# 打开文件以写入基本块信息
output_file_path = r"C:\Users\20848\Desktop\basic_blocks_output.txt"
with open(output_file_path, "w") as output_file:
    # 将基本块信息列表转换为 JSON 格式并写入文件
    for i, block_info in enumerate(basic_blocks_info):
        if i > 0:
            output_file.write(",\n")
        output_file.write("{\n")
        output_file.write(f"    name: \'{block_info['name']}\',\n")
        output_file.write(f"    x: {block_info['x']},\n")
        output_file.write(f"    y: {block_info['y']},\n")
        output_file.write(f"    block: \'{block_info['block']}\',\n")
        output_file.write(f"    assemblyCode: `\n")
        output_file.write(f"    " + block_info['assemblyCode'].replace("\n", "\n    ") + "`,\n")
        output_file.write(f"    successors: [\n")
        for j, succ in enumerate(block_info['successors']):
            if j > 0:
                output_file.write(",\n")
            output_file.write(f"        \"{succ}\"")
        output_file.write("\n    ]\n}")

    output_file.write("\n}")
