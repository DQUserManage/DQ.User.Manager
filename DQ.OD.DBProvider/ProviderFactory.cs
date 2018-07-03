using System;
using System.Collections.Generic;
using System.Data.Common;
using System.Linq;
using System.Text;

using Oracle.ManagedDataAccess.Client;
//using System.Data.SQLite;

namespace DQ.OD.DBProvider
{
    /// <summary>
    /// 数据库类型枚举
    /// </summary>
    public enum DbProviderType : byte
    {
        SqlServer,
        MySql,
        SQLite,
        Oracle,
        ODBC,
        OleDb,
        Firebird,
        PostgreSql,
        DB2,
        Informix,
        SqlServerCe
    }
    /// <summary>
    /// DbProviderFactory工厂类
    /// </summary>
    class ProviderFactory
    {
        private static Dictionary<DbProviderType, string> providerInvariantNames;
        private static Dictionary<DbProviderType, DbProviderFactory> providerFactoies;
        static ProviderFactory()
        {
            //加载已知的数据库访问类的程序集
            ProviderFactory.providerInvariantNames = new Dictionary<DbProviderType, string>();
            ProviderFactory.providerFactoies = new Dictionary<DbProviderType, DbProviderFactory>(20);

            ProviderFactory.providerInvariantNames.Add(DbProviderType.SqlServer, "System.Data.SqlClient");
            ProviderFactory.providerInvariantNames.Add(DbProviderType.OleDb, "System.Data.OleDb");
            ProviderFactory.providerInvariantNames.Add(DbProviderType.ODBC, "System.Data.ODBC");
            ProviderFactory.providerInvariantNames.Add(DbProviderType.Oracle, "Oracle.ManagedDataAccess.Client");
            ProviderFactory.providerInvariantNames.Add(DbProviderType.MySql, "MySql.Data.MySqlClient");
            ProviderFactory.providerInvariantNames.Add(DbProviderType.SQLite, "System.Data.SQLite");
            ProviderFactory.providerInvariantNames.Add(DbProviderType.Firebird, "FirebirdSql.Data.Firebird");
            ProviderFactory.providerInvariantNames.Add(DbProviderType.PostgreSql, "Npgsql");
            ProviderFactory.providerInvariantNames.Add(DbProviderType.DB2, "IBM.Data.DB2.iSeries");
            ProviderFactory.providerInvariantNames.Add(DbProviderType.Informix, "IBM.Data.Informix");
            ProviderFactory.providerInvariantNames.Add(DbProviderType.SqlServerCe, "System.Data.SqlServerCe");
        }

        public ProviderFactory()
        {
        }
        /// <summary>
        /// 获取指定数据库类型的DbProviderFactory
        /// </summary>
        /// <param name="providerType"></param>
        /// <returns></returns>
        public static DbProviderFactory GetDbProviderFactory(DbProviderType providerType)
        {
            DbProviderFactory Ada = null;
            switch (providerType)
            {
                case DbProviderType.SQLite:
                    {
                       // Ada = new SQLiteFactory();
                        break;
                    }
                case DbProviderType.Oracle:
                    {
                        Ada = new OracleClientFactory();
                        break;
                    }
                default:
                    {
                        Ada = ProviderFactory.ImportDbProviderFactory(providerType);
                        break;
                    }
            }
            return Ada;
        }
        /// <summary>
        /// 获取指定数据库类型对应的程序集名称
        /// </summary>
        /// <param name="providerType">数据库类型枚举</param>
        /// <returns></returns>
        public static string GetProviderInvariantName(DbProviderType providerType)
        {
            return ProviderFactory.providerInvariantNames[providerType];
        }
        /// <summary>
        /// 加载指定数据库类型的DbProviderFactory
        /// </summary>
        /// <param name="providerType">数据库类型枚举</param>
        /// <returns></returns>
        private static DbProviderFactory ImportDbProviderFactory(DbProviderType providerType)
        {
            string providerName = ProviderFactory.providerInvariantNames[providerType];
            DbProviderFactory factory = null;
            try
            {
                factory = DbProviderFactories.GetFactory(providerName);
            }
            catch (ArgumentException argumentException)
            {
                factory = null;
                throw new ArgumentException(argumentException.Message);
            }
            return factory;
        }

    }
}
