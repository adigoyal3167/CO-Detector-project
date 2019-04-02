from twilio.rest import Client
account_sid="AC1ed4d88759255bdc13c7bd699397940d"
auth_token ="ed7499379de0b1510f563ceabff721d1"

client= Client(account_sid, auth_token)
message= client.api.account.messages.create(
           to="+14377796894",
           from_="+14387000359",
           body="hey aditya co gas detected")
