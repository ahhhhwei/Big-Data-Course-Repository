from hbase import Hbase
from thrift.transport import TSocket, TTransport
from thrift.protocol import TBinaryProtocol
from thrift.transport.TSocket import TSocket
from thrift.transport.TTransport import TBufferedTransport
from thrift.protocol.TBinaryProtocol import TBinaryProtocolAccelerated

def deleteRow(tableName, row):
    # 创建与HBase服务器的连接
    socket = TSocket('localhost', 9090)
    transport = TBufferedTransport(socket)
    protocol = TBinaryProtocol.TBinaryProtocolAccelerated(transport)
    client = Hbase.Client(protocol)
    transport.open()

    # 删除指定行的所有数据
    client.deleteAllRow(tableName, row)  # 将行键编码为字节串

    # 关闭连接
    transport.close()

# 示例用法
table_name = "my_table"
row_key = "row1"
deleteRow(table_name, row_key)
