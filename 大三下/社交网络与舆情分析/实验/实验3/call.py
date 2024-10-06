import idaapi
import idautils

def get_acfg():
    # 获取当前正在分析的二进制文件名
    file_name = idaapi.get_root_filename()

    # 创建一个空的控制流图
    acfg = {}

    # 遍历所有函数来构建控制流图
    for func_ea in idautils.Functions():
        func_name = idaapi.get_func_name(func_ea)

        # 如果函数名不在图中，添加节点
        if func_name not in acfg:
            acfg[func_name] = []

        # 遍历当前函数的所有调用
        for (startea, endea) in idautils.Chunks(func_ea):
            for head in idautils.Heads(startea, endea):
                for ref in idautils.CodeRefsTo(head, 0):
                    caller_func = idaapi.get_func(ref)
                    if caller_func is not None:  # 判断返回值是否为 None
                        caller = idaapi.get_func_name(caller_func.start_ea)
                        if caller not in acfg[func_name]:
                            acfg[func_name].append(caller)

    return acfg

if __name__ == '__main__':
    acfg = get_acfg()
    output_file = r'C:\Users\20848\Desktop\call.txt'
    print("ACFG for", idaapi.get_root_filename())
    with open(output_file, 'w') as f:
        for func_name, callees in acfg.items():
            f.write(func_name + " <- " + ", ".join(callees) + "\n")
    print("Results written to", output_file)
