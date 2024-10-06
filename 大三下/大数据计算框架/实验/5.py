from hbase import Hbase
from thrift.transport import TSocket, TTransport
from thrift.protocol import TBinaryProtocol
from thrift.transport.TSocket import TSocket
from thrift.transport.TTransport import TBufferedTransport
from thrift.protocol.TBinaryProtocol import TBinaryProtocolAccelerated
from hbase.ttypes import Mutation

def modifyData(tableName, row, column, value):
    # 创建与HBase服务器的连接
    socket = TSocket('localhost', 9090)
    transport = TBufferedTransport(socket)
    protocol = TBinaryProtocol.TBinaryProtocolAccelerated(transport)
    client = Hbase.Client(protocol)
    transport.open()

    # 构建要修改的列的字典
    mutations = [
        Mutation(column=column, value=value)
    ]

    # 修改指定行的数据
    client.mutateRow(tableName, row, mutations)

    # 关闭连接
    transport.close()

# 示例用法
table_name = "my_table"
row_key = "row1"
column_name = "SC_Score:Math"
new_value = "95"
modifyData(table_name, row_key, column_name, new_value)