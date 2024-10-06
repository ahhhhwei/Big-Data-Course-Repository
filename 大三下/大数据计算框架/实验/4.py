from hbase import Hbase
from thrift.transport import TSocket, TTransport
from thrift.protocol import TBinaryProtocol
from thrift.transport.TSocket import TSocket
from thrift.transport.TTransport import TBufferedTransport
from thrift.protocol.TBinaryProtocol import TBinaryProtocolAccelerated

def scanColumn(tableName, column):
    # 创建与HBase服务器的连接
    socket = TSocket('localhost', 9090)
    transport = TBufferedTransport(socket)
    protocol = TBinaryProtocol.TBinaryProtocolAccelerated(transport)
    client = Hbase.Client(protocol)
    transport.open()

    # 扫描表的指定列
    scanner = client.scannerOpen(tableName, "", [column])
    row_results = client.scannerGetList(scanner, 10)  # 获取最多10行的结果列表
    for row_result in row_results:
        print("Row: %s" % row_result.row)
        # 判断列名中是否包含冒号
        if ':' in column:
            column_family, column_qualifier = column.split(':')
            column_name = f"{column_family}:{column_qualifier}"
        else:
            column_name = column
        # 检查该列是否存在于行结果中
        if column_name in row_result.columns:
            print("Column: %s, Value: %s" % (column_name, row_result.columns[column_name].value))
        else:
            print("Column %s not found in row" % column_name)

    # 关闭连接
    transport.close()

# 示例用法
table_name = "my_table"
column_name = "SC_Score:Math" 
scanColumn(table_name, column_name)
