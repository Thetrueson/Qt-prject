--CREATE TABLE Users (
--    user_id varchar(20) PRIMARY KEY ,  -- idΪ����������
--    account NVARCHAR(50) UNIQUE NOT NULL,  -- accountΪΨһ�Ҳ�Ϊ��
--    password NVARCHAR(100) NOT NULL  -- password��Ϊ��
--);

--INSERT INTO Users (user_id, account, password)
--VALUES ('U1001','admin', 'e10adc3949ba59abbe56e057f20f883e');


--CREATE TABLE Employees (
--    emp_id varchar(20) PRIMARY KEY,  -- ��������
--    name NVARCHAR(100) NOT NULL,       -- Ա������
--    sex NVARCHAR(10) NOT NULL,         -- �Ա�
--	title varchar(20) not null,
--    birthday DATE NOT NULL,            -- ��������
--    salary INT NOT NULL,    -- нˮ
--    native NVARCHAR(100) NOT NULL,     -- ����
--    user_id varchar(20) NOT NULL,              -- ����������� Users ��� id
--    hire_date DATE NOT NULL,           -- ��ְ����
--    CONSTRAINT FK_User FOREIGN KEY (user_id) REFERENCES Users(user_id)  -- ���Լ��
--);


--insert into Users(user_id,account,password) values ('U1003','emp2','e10adc3949ba59abbe56e057f20f883e')
----go
--insert into Employees (emp_id,name,sex,title,birthday,salary,native,user_id,hire_date) values('E1001','��','��','�ܹ�','2003-04-02',9000, '����', 'U1002', '2024-12-11')

--insert into Users(account,password) values ('emp2','e10adc3949ba59abbe56e057f20f883e')

--insert into Employees (name,sex,birthday,salary,native,user_id,hire_date) values('��','��','2003-07-19', 5500, '����', 3, '2024-12-10')

--select * from Employees
--select * from Users

--drop table Tasks
 --���� Tasks ��
--CREATE TABLE Tasks (
--    task_id VARCHAR(20) PRIMARY KEY,      -- �����ţ�����
--    task_name VARCHAR(50) NOT NULL,       -- ��������
--    emp_id VARCHAR(20) NOT NULL,          -- Ա����ţ����
--    execution_cycle VARCHAR(15) NOT NULL, -- ִ������
--	task_status varchar(20) NOT NULL,
--    CONSTRAINT FK_Task_Employee FOREIGN KEY (emp_id) REFERENCES Employees(emp_id) ON DELETE CASCADE  -- ���Լ��
--);

--insert into Tasks(task_id,task_name,emp_id,execution_cycle,task_status) values ('T1002','ѧϰ���ݿ�','E1002','һ��','����')

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
--    -- ��������ɾ�� Users �����뱻ɾ��Ա����صļ�¼
--    DELETE FROM Users
--    WHERE user_id in (select user_id from deleted);
--END;
--GO

--delete from Employees where emp_id = 'E1001'
--go
select * from Employees
select * from Tasks
select * from Users

