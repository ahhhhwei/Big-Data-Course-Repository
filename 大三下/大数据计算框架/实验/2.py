from hbase import Hbase
from hbase.ttypes import ColumnDescriptor, Mutation
from thrift.transport import TSocket, TTransport
from thrift.protocol import TBinaryProtocol
from thrift.transport.TSocket import TSocket
from thrift.transport.TTransport import TBufferedTransport
from thrift.protocol.TBinaryProtocol import TBinaryProtocolAccelerated

def createTable(tableName, fields):
    # 创建与HBase服务器的连接
    socket = TSocket('127.0.0.1', 9090)
    transport = TBufferedTransport(socket)
    protocol = TBinaryProtocol.TBinaryProtocolAccelerated(transport)
    client = Hbase.Client(protocol)
    transport.open()

    # 检查表是否已经存在
    tables = client.getTableNames()
    if tableName in tables:
        # 如果表已经存在，先删除原有的表
        print(f"Table '{tableName}' already exists. Deleting the existing table.")
        client.disableTable(tableName)
        client.deleteTable(tableName)

    # 定义列族
    column_descriptors = [ColumnDescriptor(name=f'{field}:') for field in fields]

    # 创建新表
    client.createTable(tableName, column_descriptors)
    print(f"Table '{tableName}' created successfully with columns: {fields}")

    # 关闭连接
    transport.close()

# 示例用法
table_name = "wjw-Student"
fields = ["SC_Sno", "SC_Cno", "SC_Score"]
createTable(table_name, fields)
