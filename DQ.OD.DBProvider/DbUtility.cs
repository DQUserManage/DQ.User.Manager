using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Data.Common;
using System.Reflection;
using System.Text.RegularExpressions;
//using System.Data.SqlClient;
using System.Windows.Forms;
using Oracle.ManagedDataAccess.Client;



namespace DQ.OD.DBProvider
{
    /// <summary>
    /// 通用数据库访问类，封装了对数据库的常见操作
    /// </summary>
    public sealed class DbUtility
    {
        public string ConnectionString { get; private set; }
        public string ErrorMessage { get; set; }
        private DbProviderFactory providerFactory;
        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="connectionString">数据库连接字符串</param>
        /// <param name="providerType">数据库类型枚举，参见<paramref name="providerType"/></param>
        public DbUtility(string connectionString, DbProviderType providerType)
        {
            ConnectionString = BuilderConnectString(providerType,connectionString);     //格式化连接串
            providerFactory = ProviderFactory.GetDbProviderFactory(providerType);
            if (providerFactory == null)
            {
                ErrorMessage = "不能根据指定的类型创建工厂类DbProviderFactory";
            }
        }

        public bool CheckLink()
        {
            ErrorMessage = "";
            try
            {
                DbConnection connection = providerFactory.CreateConnection();
                connection.ConnectionString = ConnectionString;
                connection.Open();
                connection.Close();
                return (true);
            }
            catch (Exception ex)
            {
                ErrorMessage = ex.Message;
                return (false);
            }
        }

        /// <summary>
        /// 创建参数
        /// </summary>
        /// <returns></returns>
        public DbParameter CreateDbParameter()
        {
            DbParameter parameter = this.providerFactory.CreateParameter();
            return parameter;
        }
       /// <summary>
       /// 创建参数
       /// </summary>
       /// <param name="name">参数名称</param>
       /// <param name="value">参数值</param>
       /// <returns></returns>
        public DbParameter CreateDbParameter(string name, object value)
        {
            return this.CreateDbParameter(name, ParameterDirection.Input, value);
        }
        /// <summary>
        /// 创建参数
        /// </summary>
        /// <param name="name">参数名称</param>
        /// <param name="parameterDirection">参数类型，输入、输出、双向</param>
        /// <param name="value">参数值</param>
        /// <returns></returns>
        public DbParameter CreateDbParameter(string name, ParameterDirection parameterDirection, object value)
        {
            DbParameter parameter = this.providerFactory.CreateParameter();
            parameter.ParameterName = name;
            parameter.Value = value;
            parameter.Direction = parameterDirection;
            return parameter;
        }
        /// <summary>
        /// 获取EXCEL第一个SHETT页的名称
        /// </summary>
        /// <returns></returns>
        public String GetExcelFirstSheetName()
        {
            String strSheetName = "";
            using (DbConnection connection = providerFactory.CreateConnection())
            {
                connection.ConnectionString = ConnectionString;
                connection.Open();
                DataTable sheetNames = connection.GetSchema("Tables");
                connection.Close();
                foreach (DataRow dr in sheetNames.Rows)
                {
                    strSheetName = dr[2].ToString();
                    break;
                }
            }

            return strSheetName;
        }

#region 数据库操作
        /// <summary>   
        /// 对数据库执行增删改操作，返回受影响的行数。   
        /// </summary>   
        /// <param name="sql">要执行的增删改的SQL语句</param>   
        /// <param name="parameters">执行增删改语句所需要的参数</param>
        /// <returns></returns>  
        public int ExecuteNonQuery(string sql, IList<DbParameter> parameters)
        {
            return ExecuteNonQuery(sql, parameters, CommandType.Text);
        }
        public int ExecuteNonQuery(List<String> SQLList)
        {
            ErrorMessage = "";
            using (DbConnection conntion = providerFactory.CreateConnection())
            {
                conntion.ConnectionString = ConnectionString;
                conntion.Open();
                DbCommand command = providerFactory.CreateCommand();
                command.Connection = conntion;

                DbTransaction ts = conntion.BeginTransaction();
                command.Transaction = ts;
                string strsql = "";
                try
                {
                    int count = 0;
                    for (int i = 0; i < SQLList.Count; i++)
                    {
                        strsql = SQLList[i];
                        if (strsql.Length > 1)
                        {
                            command.CommandText = strsql;
                            count += command.ExecuteNonQuery();
                        }
                    }
                    ts.Commit();//提交数据库事务
                    conntion.Close();
                    return count;
                }
                catch (Exception ex)
                {
                    ErrorMessage = ex.Message + "\r\nSQL:" + strsql;
                    ts.Rollback();
                    conntion.Close();
                    return 0;
                }
            }
        }
        /// <summary>   
        /// 对数据库执行增删改操作，返回受影响的行数。   
        /// </summary>   
        /// <param name="sql">要执行的增删改的SQL语句</param>   
        /// <param name="parameters">执行增删改语句所需要的参数</param>
        /// <param name="commandType">执行的SQL语句的类型</param>
        /// <returns></returns>
        public int ExecuteNonQuery(string sql, IList<DbParameter> parameters, CommandType commandType)
        {
            ErrorMessage = "";
            using (DbCommand command = CreateDbCommand(sql, parameters, commandType))
            {
                try
                {
                    command.Connection.Open();
                    int affectedRows = command.ExecuteNonQuery();
                    command.Connection.Close();
                    return affectedRows;
                }
                catch (Exception ex)
                {
                    ErrorMessage = ex.Message + "\r\nSQL:" + sql;
                    return (-1);
                }
            }
        }
        /// <summary>   
        /// 执行一个查询语句，返回一个关联的DataReader实例   
        /// </summary>   
        /// <param name="sql">要执行的查询语句</param>   
        /// <param name="parameters">执行SQL查询语句所需要的参数</param>
        /// <returns></returns> 
        public DbDataReader ExecuteReader(string sql, IList<DbParameter> parameters)
        {
            return ExecuteReader(sql, parameters, CommandType.Text);
        }
        /// <summary>   
        /// 执行一个查询语句，返回一个关联的DataReader实例   
        /// </summary>   
        /// <param name="sql">要执行的查询语句</param>   
        /// <param name="parameters">执行SQL查询语句所需要的参数</param>
        /// <param name="commandType">执行的SQL语句的类型</param>
        /// <returns></returns> 
        public DbDataReader ExecuteReader(string sql, IList<DbParameter> parameters, CommandType commandType)
        {
            ErrorMessage = "";
            try
            {
                DbCommand command = CreateDbCommand(sql, parameters, commandType);
                command.Connection.Open();
                return command.ExecuteReader(CommandBehavior.CloseConnection);
            }
            catch (Exception ex)
            {
                ErrorMessage = ex.Message + "\r\nSQL:" + sql;
                return (null);
            }
        }
        /// <summary>   
        /// 执行一个查询语句，返回一个包含查询结果的DataTable   
        /// </summary>   
        /// <param name="sql">要执行的查询语句</param>   
        /// <param name="parameters">执行SQL查询语句所需要的参数</param>
        /// <returns></returns>
        public DataTable ExecuteDataTable(string sql, IList<DbParameter> parameters)
        {
            return ExecuteDataTable(sql, parameters, CommandType.Text);
        }
        /// <summary>   
        /// 执行一个查询语句，返回一个包含查询结果的DataTable   
        /// </summary>   
        /// <param name="sql">要执行的查询语句</param>   
        /// <param name="parameters">执行SQL查询语句所需要的参数</param>
        /// <param name="commandType">执行的SQL语句的类型</param>
        /// <returns></returns>
        public DataTable ExecuteDataTable(string sql, IList<DbParameter> parameters, CommandType commandType)
        {
            ErrorMessage = "";
            try
            {
                using (DbCommand command = CreateDbCommand(sql, parameters, commandType))
                {
                    using (DbDataAdapter adapter = providerFactory.CreateDataAdapter())
                    {
                        adapter.SelectCommand = command;
                        DataTable data = new DataTable();
                        data.TableName = GetTableName(sql);
                        adapter.Fill(data);
                        data.ExtendedProperties.Add("SQL", sql);
                        return data;
                    }
                }
            }
            catch (Exception ex)
            {
                ErrorMessage = ex.Message + "\r\nSQL:" + sql;
                return (new DataTable());
            }
        }
        /// <summary>   
        /// 执行一个查询语句，返回一个包含查询结果的DataTable  ,Oracle模式连接 
        /// </summary>   
        /// <param name="sql">要执行的查询语句</param>   
        /// <param name="parameters">执行SQL查询语句所需要的参数</param>
        /// <returns></returns>
        public DataTable ExecuteOrclDataTable(string sql, IList<DbParameter> parameters)
        {
            return ExecuteOrclDataTable(sql, parameters, CommandType.Text);
        }
        /// <summary>   
        /// 执行一个查询语句，返回一个包含查询结果的DataTable , Oracle模式连接
        /// </summary>   
        /// <param name="sql">要执行的查询语句</param>   
        /// <param name="parameters">执行SQL查询语句所需要的参数</param>
        /// <param name="commandType">执行的SQL语句的类型</param>
        /// <returns></returns>
        public DataTable ExecuteOrclDataTable(string sql, IList<DbParameter> parameters, CommandType commandType)
        {
            ErrorMessage = "";
            try
            {
                using (OracleConnection conn = new OracleConnection(ConnectionString))
                {
                    conn.Open();
                    using (OracleCommand cmd = conn.CreateCommand())
                    {
                        cmd.CommandType = commandType;
                        cmd.CommandText = sql;
                        cmd.InitialLONGFetchSize = -1;
                        if (!(parameters == null || parameters.Count == 0))
                        {
                            foreach (DbParameter parameter in parameters)
                            {
                                cmd.Parameters.Add(parameter);
                            }
                        }
                        using (DbDataAdapter adapter = providerFactory.CreateDataAdapter())
                        {
                            adapter.SelectCommand = cmd;
                            DataTable data = new DataTable();
                            data.TableName = GetTableName(sql);
                            adapter.Fill(data);
                            data.ExtendedProperties.Add("SQL", sql);
                            return data;
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                ErrorMessage = ex.Message + "\r\nSQL:" + sql;
                return (new DataTable());
            }
        }
         /// <summary>   
        /// 执行一个查询语句，返回记录个数  
        /// </summary>   
        /// <param name="sql">要执行的查询语句</param>   
        /// <param name="parameters">执行SQL查询语句所需要的参数</param>   
        /// <returns></returns>   
        public int ExecuteRowsCount(string sql, IList<DbParameter> parameters)
        {

            return Convert.ToInt32(ExecuteScalar(sql, parameters, CommandType.Text));
        }
        /// <summary>   
        /// 执行一个查询语句，返回查询结果的第一行第一列   
        /// </summary>   
        /// <param name="sql">要执行的查询语句</param>   
        /// <param name="parameters">执行SQL查询语句所需要的参数</param>   
        /// <returns></returns>   
        public Object ExecuteScalar(string sql, IList<DbParameter> parameters)
        {
            return ExecuteScalar(sql, parameters, CommandType.Text);
        }
        public Object ExecuteScalar(string sql)
        {
            Object obj = ExecuteScalar(sql, null);
            return (obj);
        }
        /// <summary>     
        /// 执行一个查询语句，返回查询结果的第一行第一列     
        /// </summary>     
        /// <param name="sql">要执行的查询语句</param>     
        /// <param name="parameters">执行SQL查询语句所需要的参数</param>     
        /// <param name="commandType">执行的SQL语句的类型</param>  
        /// <returns></returns>     
        public Object ExecuteScalar(string sql, IList<DbParameter> parameters, CommandType commandType)
        {
            ErrorMessage = "";
            try
            {
                using (DbCommand command = CreateDbCommand(sql, parameters, commandType))
                {
                    command.Connection.Open();
                    object result = command.ExecuteScalar();
                    command.Connection.Close();
                    return result;
                }
            }
            catch (Exception ex)
            {
                ErrorMessage = ex.Message + "\r\nSQL:" + sql;
                return (null);
            }
        }
        /// <summary>   
        /// 执行存储过程，返回int  
        /// </summary>   
        /// <param name="storedProcName">存储过程名</param>   
        /// <param name="parameters">存储过程参数</param>   
        /// <returns></returns>  
        public int ExecuteProcedure(string storedProcName, IList<DbParameter> parameters)
        {
            ErrorMessage = "";
            try
            {
                using (DbCommand command = CreateDbCommand(storedProcName, parameters, CommandType.StoredProcedure))
                {
                    command.Connection.Open();
                    int affectedRows = command.ExecuteNonQuery();
                    command.Connection.Close();
                    return affectedRows;
                }
            }
            catch (Exception ex)
            {
                ErrorMessage = ex.Message + "\r\nSQL:" + storedProcName;
                return 0;
            }
        }
        /// <summary>     
        /// 更新table到数据库    
        /// </summary>     
        /// <param name="dt">要更新的表</param>     
        /// <param name="sql">要执行的查询语句</param>     
        /// <returns></returns> 
        public int UpdateTable(DataTable dt, string sql)
        {
            ErrorMessage = "";
            int affect = 0;
            DbConnection connection = providerFactory.CreateConnection();
            using (DbCommand command = CreateDbCommand(sql, null, CommandType.Text))
            {
                using (DbDataAdapter adapter = providerFactory.CreateDataAdapter())
                {
                    command.CommandType = CommandType.Text;
                    //command.CommandText = sql;
                    command.CommandText = dt.ExtendedProperties["SQL"].ToString();
                    adapter.SelectCommand = command;
                    adapter.MissingSchemaAction = MissingSchemaAction.AddWithKey;
                    using (DbCommandBuilder cb = providerFactory.CreateCommandBuilder())
                    {
                        try
                        {
                            cb.DataAdapter = adapter;
                            adapter.InsertCommand = cb.GetInsertCommand();
                            adapter.UpdateCommand = cb.GetUpdateCommand();
                            adapter.DeleteCommand = cb.GetDeleteCommand();

                            adapter.UpdateCommand.UpdatedRowSource = UpdateRowSource.None;
                            adapter.InsertCommand.UpdatedRowSource = UpdateRowSource.None;
                            adapter.DeleteCommand.UpdatedRowSource = UpdateRowSource.None;

                            command.Connection.Open();
                            if (dt.GetChanges() != null)
                            {
                                affect = adapter.Update(dt.GetChanges());
                                dt.AcceptChanges();
                            }
                            command.Connection.Close();
                        }
                        catch (Exception ex)
                        {
                            ErrorMessage = ex.Message;
                            affect = -1;
                        }
                    }

                }
            }

            return affect;
        }
        /// <summary>     
        /// 批量插入    
        /// </summary>     
        /// <param name="dt">要插入的表</param>     
        /// <param name="sql">要执行的查询语句</param>     
        /// <returns></returns> 
        public void BatchInsert(DataTable dt, string sql)
        {
            ErrorMessage = "";
            if (dt.Rows.Count == 0) return;
            DbConnection connection = providerFactory.CreateConnection();
            connection.ConnectionString = ConnectionString;
            DbCommand command = CreateDbCommand(sql, null, CommandType.Text);
            using (DbDataAdapter adapter = providerFactory.CreateDataAdapter())
            {
                adapter.SelectCommand = command;
                adapter.MissingSchemaAction = MissingSchemaAction.AddWithKey;
                DbCommandBuilder cb = providerFactory.CreateCommandBuilder();
                cb.DataAdapter = adapter;
                adapter.InsertCommand = cb.GetInsertCommand();
                command.Connection.Open();
                DbTransaction dbTrans = command.Connection.BeginTransaction();
                DbParameterCollection Valuelist = adapter.InsertCommand.Parameters;
                try
                {
                    for (int i = 0; i < dt.Rows.Count; i++)
                    {
                        DataRow dr = dt.Rows[i];
                        for (int j = 0; j < Valuelist.Count; j++)
                            Valuelist[j].Value = dr[Valuelist[j].SourceColumn];
                        adapter.InsertCommand.ExecuteNonQuery();
                    }
                    dbTrans.Commit();
                }
                catch (Exception ex)
                {
                    if (dbTrans != null)
                        dbTrans.Rollback();
                    ErrorMessage = ex.Message;
                }
                command.Connection.Close();
            }
        }
        /// <summary>     
        /// 分组    
        /// </summary>     
        /// <returns></returns> 
        public DataTable GroupBy(DataTable srcDatatable, string Selectlist, string groupbylist, string filterexpression, string Sortexpression)
        {
            groupbylist = groupbylist.ToUpper().Trim();
            Selectlist = Selectlist.ToUpper().Trim();
            string[] groupfield = groupbylist.Split(',');
            string[] fields = Selectlist.Split(',');
            DataView dv = srcDatatable.DefaultView;
            //过滤
            dv.RowFilter = filterexpression;
            dv.Sort = Sortexpression;
            DataTable DtFilter = dv.ToTable();
            //分组
            DataTable GroupTable = dv.ToTable(true, groupfield);
            DataTable Result = GroupTable.Copy();
            //添加列
            for (int i = 0; i < fields.GetLength(0); i++)
            {
                foreach (DataColumn dc in DtFilter.Columns)
                {
                    if (fields[i].IndexOf(dc.ColumnName.ToUpper()) >= 0)
                    {
                        if (groupbylist.IndexOf(fields[i]) >= 0) break;//分组已经添加
                        DataColumn newdc = new DataColumn(fields[i]);
                        newdc.DataType = dc.DataType;
                        Result.Columns.Add(newdc);
                        break;
                    }
                }
            }
            //计算汇总            
            foreach (DataRow r in Result.Rows)
            {
                for (int i = 0; i < fields.GetLength(0); i++)
                {
                    if (groupbylist.IndexOf(fields[i]) >= 0) continue;
                    if (Result.Columns[fields[i]].DataType == typeof(String)) continue;
                    string condition = "";
                    for (int j = 0; j < groupfield.GetLength(0); j++)
                    {
                        condition += groupfield[j] + "='" + r[groupfield[j]].ToString() + "' AND ";
                    }
                    condition = condition.Substring(0, condition.Length - 5); ;
                    r[fields[i]] = DtFilter.Compute(fields[i], condition);
                }
            }
            return (Result);
        }
        public DataTable GroupStruct(DataTable srcDatatable, string groupbylist, bool ShowSubtotal, bool ShowTotal)
        {
            groupbylist = groupbylist.ToUpper().Trim();
            string[] groupfield = groupbylist.Split(',');
            DataView dv = srcDatatable.DefaultView;
            //排序
            dv.Sort = groupbylist;
            //分组
            DataTable GroupTable = dv.ToTable(true, groupfield);
            DataColumn col = new DataColumn("Condition", typeof(string));
            GroupTable.Columns.Add(col);
            //添加条件
            string condition;
            for (int i = 0; i < GroupTable.Rows.Count; i++)
            {
                DataRow dr = GroupTable.Rows[i];
                condition = "";
                for (int j = 0; j < groupfield.GetLength(0); j++)
                {
                    condition += String.Format("{0}='{1}' And ", groupfield[j], dr[groupfield[j]]);
                }
                condition = condition.Remove(condition.Length - 4);
            }
            string field;
            if (ShowSubtotal)//小计
            {
                for (int i = 0; i < groupfield.GetLength(0); i++)
                {
                    field = groupfield[i];
                    for (int j = 1; j < GroupTable.Rows.Count; j++)
                    {
                        if (GroupTable.Rows[j][i] != GroupTable.Rows[j - 1][i])
                        {
                            DataRow dr = GroupTable.NewRow();
                            dr[0] = "Subtotal";
                            dr["Condition"] = GroupTable.Rows[j - 1]["Condition"];
                            GroupTable.Rows.InsertAt(dr, i);
                        }
                    }
                }
            }
            if (ShowTotal)//总计
            {
                DataRow dr = GroupTable.NewRow();
                dr[0] = "Total";
                GroupTable.Rows.Add(dr);
            }
            return (GroupTable);
        }

#endregion

        /// <summary>
        /// 创建一个DbCommand对象
        /// </summary>
        /// <param name="sql">要执行的查询语句</param>   
        /// <param name="parameters">执行SQL查询语句所需要的参数</param>
        /// <param name="commandType">执行的SQL语句的类型</param>
        /// <returns></returns>
        private DbCommand CreateDbCommand(string sql, IList<DbParameter> parameters, CommandType commandType)
        {
            DbConnection connection = providerFactory.CreateConnection();
            DbCommand command = providerFactory.CreateCommand();
            connection.ConnectionString = ConnectionString;
            command.CommandText = sql;
            command.CommandType = commandType;
            command.Connection = connection;
            if (!(parameters == null || parameters.Count == 0))
            {
                foreach (DbParameter parameter in parameters)
                {
                    command.Parameters.Add(parameter);
                }
            }
            return command;
        }

        /// <summary>
        /// 格式化数据链接
        /// </summary>
        /// <param name="Type"></param>
        /// <param name="DataSource"></param>
        private string BuilderConnectString(DbProviderType Type, string DataSource)
        {
            string connectionString = DataSource;
            if (Type == DbProviderType.SqlServer)
            {
                
            }
            else if (Type == DbProviderType.MySql)
            {

            }
            else if (Type == DbProviderType.SQLite)
            {
                connectionString = string.Format("Data Source={0}", DataSource);
            }
            else if (Type == DbProviderType.Oracle)
            {
                connectionString = string.Format("Data Source={0}", DataSource);
            }
            else if (Type == DbProviderType.OleDb)
            {
                //根据数据源分为07格式与03格式,07为.xlsx
                string sFileExtension = System.IO.Path.GetExtension(DataSource);       //获取文件扩展名
                if (string.Compare(sFileExtension, ".xls", true) == 0)
                {
                    connectionString = string.Format("Provider=Microsoft.Jet.OLEDB.4.0;Data Source={0};Extended Properties='Excel 8.0;HDR=Yes;IMEX=1;'", DataSource);
                }
                else if (string.Compare(sFileExtension, ".xlsx", true) == 0)
                {
                    connectionString = string.Format("Provider=Microsoft.ACE.OLEDB.12.0;Data Source={0};Extended Properties='Excel 12.0;HDR=Yes;IMEX=1;'", DataSource);
                }
                else /*if (string.Compare(sFileExtension, ".dbf", true) == 0)*/
                {
                    connectionString = string.Format("Provider=Microsoft.ACE.OLEDB.12.0;Data Source={0};Extended Properties='dBASE 5.0';User ID = Admin;Password =;", DataSource);
                }
//                 else
//                 {
//                     connectionString = string.Format("Provider=Microsoft.ACE.OLEDB.12.0;Data Source={0};Extended Properties='text;HDR=Yes;FMT=Delimited';", DataSource);
//                     //connectionString = string.Format("Provider=Microsoft.Jet.OLEDB.4.0;Data Source={0};Extended Properties='text;HDR=no;FMT=Delimited;'", DataSource);
//                 }
            }
            else if (Type == DbProviderType.Firebird)
            {

            }
            else if (Type == DbProviderType.PostgreSql)
            {

            }
            else if (Type == DbProviderType.DB2)
            {
            }
            else if (Type == DbProviderType.Informix)
            {

            }

            return connectionString;
        }

        /// <summary>
        /// 获取表名
        /// </summary>
        /// <param name="StrSql">SQL语句</param>
        private string GetTableName(string StrSql)
        {
            if (!string.IsNullOrEmpty(StrSql) && StrSql.IndexOf("select", StringComparison.CurrentCultureIgnoreCase) >= 0)
            {
                string str = StrSql.Replace("\n", " ");
                int index = str.IndexOf(" from ", StringComparison.CurrentCultureIgnoreCase);
                return str.Substring(index + 5).Trim().Split(new char[] { ' ', ',' })[0];
            }
            return "";
        }

    }

}
