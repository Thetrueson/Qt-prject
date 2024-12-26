--CREATE TABLE Users (
--    user_id varchar(20) PRIMARY KEY ,  -- id为主键，自增
--    account NVARCHAR(50) UNIQUE NOT NULL,  -- account为唯一且不为空
--    password NVARCHAR(100) NOT NULL  -- password不为空
--);

--INSERT INTO Users (user_id, account, password)
--VALUES ('U1001','admin', 'e10adc3949ba59abbe56e057f20f883e');


--CREATE TABLE Employees (
--    emp_id varchar(20) PRIMARY KEY,  -- 自增主键
--    name NVARCHAR(100) NOT NULL,       -- 员工姓名
--    sex NVARCHAR(10) NOT NULL,         -- 性别
--	title varchar(20) not null,
--    birthday DATE NOT NULL,            -- 出生日期
--    salary INT NOT NULL,    -- 薪水
--    native NVARCHAR(100) NOT NULL,     -- 籍贯
--    user_id varchar(20) NOT NULL,              -- 外键，关联到 Users 表的 id
--    hire_date DATE NOT NULL,           -- 入职日期
--    CONSTRAINT FK_User FOREIGN KEY (user_id) REFERENCES Users(user_id)  -- 外键约束
--);


--insert into Users(user_id,account,password) values ('U1003','emp2','e10adc3949ba59abbe56e057f20f883e')
----go
--insert into Employees (emp_id,name,sex,title,birthday,salary,native,user_id,hire_date) values('E1001','罗','男','总管','2003-04-02',9000, '江西', 'U1002', '2024-12-11')

--insert into Users(account,password) values ('emp2','e10adc3949ba59abbe56e057f20f883e')

--insert into Employees (name,sex,birthday,salary,native,user_id,hire_date) values('威','男','2003-07-19', 5500, '江西', 3, '2024-12-10')

--select * from Employees
--select * from Users

--drop table Tasks
 --创建 Tasks 表
--CREATE TABLE Tasks (
--    task_id VARCHAR(20) PRIMARY KEY,      -- 任务编号，主键
--    task_name VARCHAR(50) NOT NULL,       -- 任务名称
--    emp_id VARCHAR(20) NOT NULL,          -- 员工编号，外键
--    execution_cycle VARCHAR(15) NOT NULL, -- 执行周期
--	task_status varchar(20) NOT NULL,
--    CONSTRAINT FK_Task_Employee FOREIGN KEY (emp_id) REFERENCES Employees(emp_id) ON DELETE CASCADE  -- 外键约束
--);

--insert into Tasks(task_id,task_name,emp_id,execution_cycle,task_status) values ('T1002','学习数据库','E1002','一周','待办')

--create trigger taskdel on Tasks for delete
--as delete from Employees where emp_id in(select emp_id from deleted)
--go
--create trigger empdel on Employees for delete
--as delete from Users where user_id in(select user_id from deleted)

--drop trigger empdel
--go
--CREATE TRIGGER empdel ON Employees FOR DELETE
--AS
--BEGIN
--    -- 第三步：删除 Users 表中与被删除员工相关的记录
--    DELETE FROM Users
--    WHERE user_id in (select user_id from deleted);
--END;
--GO

--delete from Employees where emp_id = 'E1001'
--go
select * from Employees
select * from Tasks
select * from Users

