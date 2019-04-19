import mysql.connector
import getpass

HOST="localhost"
DATABASE="Fabryka_Sprzetu_IT"
SQL=("SELECT * FROM Produkt;")


print("Welcome to MySQL connector. \nYou are trying to connect to host: " + HOST + "\nType your credentials to connect:")

while(True):
    print("User: ", end='')
    user=input()
    password=getpass.getpass()
    print()
    try:
        sqlDatabase = mysql.connector.connect(host=HOST, user=user, passwd=password, database=DATABASE)
        break
    except mysql.connector.Error as e:
        print(e)
        if e.errno!=1045:
            exit()
        else:
            print("Try again.\n")
            

curs=sqlDatabase.cursor()
print(SQL)
curs.execute(SQL)
res=curs.fetchall()

for r in res:
    print(r)

