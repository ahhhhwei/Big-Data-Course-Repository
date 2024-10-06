from hbase import Hbase
from hbase.ttypes import ColumnDescriptor, Mutation
from thrift.transport import TSocket, TTransport
from thrift.protocol import TBinaryProtocol
from thrift.transport.TSocket import TSocket
from thrift.transport.TTransport import TBufferedTransport
from thrift.protocol.TBinaryProtocol import TBinaryProtocolAccelerated

def addRecord(tableName, row, mutations):
    # 创建与HBase服务器的连接
    socket = TSocket('localhost', 9090)
    transport = TBufferedTransport(socket)
    protocol = TBinaryProtocol.TBinaryProtocolAccelerated(transport)
    client = Hbase.Client(protocol)
    transport.open()

    # 添加记录
    client.mutateRow(tableName, row, mutations)

    print("Record added successfully.")

    # 关闭连接
    transport.close()

# 示例用法
table_name = "my_table"
row_key = "row1"  
mutations = [
    Mutation(column="SC_Cno:C1", value="value1"),
    Mutation(column="SC_Score:Math", value="90"),
    Mutation(column="SC_Sno:S1", value="123456")
]
addRecord(table_name, row_key, mutations)
