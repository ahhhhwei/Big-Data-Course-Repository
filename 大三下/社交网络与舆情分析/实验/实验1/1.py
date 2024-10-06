import os
import sys

androguard_module_path = os.path.join( os.path.dirname(os.path.abspath(__file__)), 'androguard' )
if not androguard_module_path in sys.path:
    sys.path.append(androguard_module_path)
    
from androguard.misc import AnalyzeAPK
from androguard.core.androconf import load_api_specific_resource_module

path = r"D:\编程\阿伟的笔记本\大三下\舆情分析\实验\apk"
out_path = r"D:\编程\阿伟的笔记本\大三下\舆情分析\实验\out"
files = []
path_list=os.listdir(path)
path_list.sort()
for name in path_list:
        if os.path.isfile(os.path.join(path, name)):
            files.append(name)

def main():
    for apkfile in files:
        file_name = os.path.splitext(apkfile)[0]   
        out = AnalyzeAPK(path + '\\' + apkfile) 
        # 权限
        a = out[0]
        permissions = a.get_permissions()
        print("Permissions:")
        print("\n".join(permissions))
        dx = out[2]
        # api，太多了，写入文件中      
        api_perm_filename = os.path.join(out_path, file_name + "_api.txt")
        api_perm_file = open(api_perm_filename, 'w', encoding='utf-8')
        results = []
        for meth_analysis in dx.get_methods():
            meth = meth_analysis.get_method()
            result = str(meth)
            api_perm_file.write(result + '\n')  
        api_perm_file.close()

        # intents
        android_manifest_xml = a.get_android_manifest_xml()
        print("Intents:")
        for activity in android_manifest_xml.findall(".//activity"):
            for intent_filter in activity.findall(".//intent-filter"):
                for action in intent_filter.findall(".//action"):
                    print(action.attrib['{http://schemas.android.com/apk/res/android}name'])

if __name__=='__main__':
    main()

