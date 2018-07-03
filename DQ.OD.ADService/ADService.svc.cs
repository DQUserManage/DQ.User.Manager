using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;
using System.DirectoryServices;
using System.Configuration;
using System.Security.Cryptography;


namespace DQODADService
{
    // 注意: 使用“重构”菜单上的“重命名”命令，可以同时更改代码、svc 和配置文件中的类名“Service1”。
    // 注意: 为了启动 WCF 测试客户端以测试此服务，请在解决方案资源管理器中选择 Service1.svc 或 Service1.svc.cs，然后开始调试。
    public class ADService : IADService
    {
        public bool CheckADUser(String sUserName, String sPassword, ref String strDBConString)
        {

            strDBConString = Encrypt(ConfigurationManager.ConnectionStrings["ProjectDBConstring"].ToString());

            return true;

            string LDAPPATH = ConfigurationManager.ConnectionStrings["ADPath"].ToString();
            DirectoryEntry entry = null;
            try
            {
                entry = new DirectoryEntry(LDAPPATH, sUserName, sPassword);
                DirectorySearcher mySearcher = new DirectorySearcher(entry);
                mySearcher.Filter = "(SAMAccountName=" + sUserName + ")";
                SearchResult result = mySearcher.FindOne();
                if (result == null)
                {
                    return false;
                }
                else
                {
                    //获取AD域用户的具体信息
                    DirectoryEntry a = result.GetDirectoryEntry();
                    string strdw = a.Parent.Parent.Name.Substring(a.Parent.Parent.Name.LastIndexOf("=") + 1);
                    string strdw1 = a.Parent.Name.Substring(a.Parent.Name.LastIndexOf("=") + 1);

                    string strname;
                    strname = result.GetDirectoryEntry().Name.ToString();
                    ResultPropertyCollection myResultPropColl;
                    myResultPropColl = result.Properties;
                    strname = "";
                    foreach (Object myCollection in myResultPropColl["displayname"])
                    {
                        strname += myCollection;
                        break;
                    }


                    //获取数据库链接字符串，并进行加密，客户端接收数据后则进行解密

                    strDBConString = Encrypt(ConfigurationManager.ConnectionStrings["ProjectDBConstring"].ToString());

                    return true;
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message); 
                return false;
            }
        }
        /// <summary>
        /// 256位AES加密
        /// </summary>
        /// <param name="toEncrypt"></param>
        /// <returns></returns>
        public string Encrypt(string toEncrypt)
        {
            // 256-AES key    
            byte[] keyArray = UTF8Encoding.UTF8.GetBytes("12345678901234567890123456789012");
            byte[] toEncryptArray = UTF8Encoding.UTF8.GetBytes(toEncrypt);

            RijndaelManaged rDel = new RijndaelManaged();
            rDel.Key = keyArray;
            rDel.Mode = CipherMode.ECB;
            rDel.Padding = PaddingMode.PKCS7;

            ICryptoTransform cTransform = rDel.CreateEncryptor();
            byte[] resultArray = cTransform.TransformFinalBlock(toEncryptArray, 0, toEncryptArray.Length);

            return Convert.ToBase64String(resultArray, 0, resultArray.Length);
        }


    }
}
