using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Windows.Forms;

namespace DQ.OD.DBProvider
{
    /// <summary>
    /// AD域用户认证
    /// </summary>
   public class CheckADUserHelp
   {
      /// <summary>
        ///  验证AD用户
      /// </summary>
      /// <param name="strUserName"></param>
      /// <param name="strPassword"></param>
      /// <param name="strADServiceAddress"></param>
      /// <returns></returns>
       public String CheckADUser(String strUserName, String strPassword, String strADServiceAddress)
       {
           ADService.IADService proxy = WcfInvokeFactory.CreateServiceByUrl<ADService.IADService>(strADServiceAddress);

           String strDBConstring = "";
           try
           {
               bool bCheck = proxy.CheckADUser(strUserName, strPassword, ref strDBConstring);
               strDBConstring = Decrypt(strDBConstring);
           }catch(Exception err)
           {
                err.GetType();
               MessageBox.Show("服务地址不正确！" + strADServiceAddress+",请联系系统管理员。", "错误",MessageBoxButtons.OK,MessageBoxIcon.Error); 
           }

           return strDBConstring;      //解密字符串
       }
       /// <summary>
       /// 256位AES解密
       /// </summary>
       /// <param name="toDecrypt"></param>
       /// <returns></returns>
       public static string Decrypt(string toDecrypt)
       {
           // 256-AES key    
           byte[] keyArray = UTF8Encoding.UTF8.GetBytes("12345678901234567890123456789012");
           byte[] toEncryptArray = Convert.FromBase64String(toDecrypt);

           RijndaelManaged rDel = new RijndaelManaged();
           rDel.Key = keyArray;
           rDel.Mode = CipherMode.ECB;
           rDel.Padding = PaddingMode.PKCS7;

           ICryptoTransform cTransform = rDel.CreateDecryptor();
           byte[] resultArray = cTransform.TransformFinalBlock(toEncryptArray, 0, toEncryptArray.Length);

           return UTF8Encoding.UTF8.GetString(resultArray);
       }

    }
}
