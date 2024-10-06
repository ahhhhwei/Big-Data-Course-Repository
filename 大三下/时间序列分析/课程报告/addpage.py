import PyPDF2

def merge_pdfs(pdf1_path, pdf2_path, output_path):
    # 打开第一个 PDF 文件
    with open(pdf1_path, 'rb') as pdf1_file:
        pdf1_reader = PyPDF2.PdfReader(pdf1_file)
        first_page = pdf1_reader.pages[0]  # 获取第一页

        # 打开第二个 PDF 文件
        with open(pdf2_path, 'rb') as pdf2_file:
            pdf2_reader = PyPDF2.PdfReader(pdf2_file)
            # 创建一个新的 PDF 写入对象
            pdf_writer = PyPDF2.PdfWriter()

            # 将第一页插入到新 PDF 的首页
            pdf_writer.add_page(first_page)

            # 将第二个 PDF 的所有页面添加到新 PDF 中
            for page_num in range(len(pdf2_reader.pages)):
                page = pdf2_reader.pages[page_num]
                pdf_writer.add_page(page)

            # 将合并后的 PDF 写入到输出文件中
            with open(output_path, 'wb') as output_file:
                pdf_writer.write(output_file)
                
# 调用函数并传入文件路径
pdf1_path = '报告封面.pdf'
pdf2_path = '时间序列分析期末预习.pdf'
output_path = '时间序列分析课程报告_温家伟_202103151422.pdf'

merge_pdfs(pdf1_path, pdf2_path, output_path)
