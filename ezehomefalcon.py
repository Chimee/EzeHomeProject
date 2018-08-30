# ezehomefalcon.py


import sys
import requests
import json
import falcon


#light manipulation functions
#Url to Smartthings Endpoint



def allofthelight_allofthelights():

    command_url = "http://graph-na02-useast1.api.smartthings.com/api/smartapps/installations/11fecf77-79a0-4f55-afbe-ab8d08ef0274/switches/toggle"
    command_param = {
        "access_token": "14e22dff-7a8e-440c-84dd-6c4a103f075b"
    }
    command_header = {}

##Display endpoint accessed in terminal
    print(command_url)
    command_response = requests.put(
        url=command_url, 
        params=command_param, 
        headers=command_header, 
        data=({"command": "toggle"})
    )
    
def toggle_trin():

    command_url = "http://graph-na02-useast1.api.smartthings.com/api/smartapps/installations/11fecf77-79a0-4f55-afbe-ab8d08ef0274/switches/TrinsLight/toggle"
    command_param = {
        "access_token": "14e22dff-7a8e-440c-84dd-6c4a103f075b"
    }
    command_header = {}


    print(command_url)
    command_response = requests.put(
        url=command_url, 
        params=command_param, 
        headers=command_header,
        data=({"command": "toggle"})
    )


def toggle_captain():

    command_url = "http://graph-na02-useast1.api.smartthings.com/api/smartapps/installations/11fecf77-79a0-4f55-afbe-ab8d08ef0274/switches/CaptainsLight/toggle"
    command_param = {
        "access_token": "14e22dff-7a8e-440c-84dd-6c4a103f075b"
    }
    command_header = {}


    print(command_url)
    command_response = requests.put(
        url=command_url, 
        params=command_param, 
        headers=command_header,
        data=({"command": "toggle"})
    )    
        


def toggle_stairs():

    command_url = "http://graph-na02-useast1.api.smartthings.com/api/smartapps/installations/11fecf77-79a0-4f55-afbe-ab8d08ef0274/switches/StairsLight/toggle"
    command_param = {
        "access_token": "14e22dff-7a8e-440c-84dd-6c4a103f075b"
    }
    command_header = {}


    print(command_url)
    command_response = requests.put(
        url=command_url, 
        params=command_param, 
        headers=command_header,
        data=({"command": "toggle"})
    )


def toggle_lr():

    command_url = "http://graph-na02-useast1.api.smartthings.com/api/smartapps/installations/11fecf77-79a0-4f55-afbe-ab8d08ef0274/switches/LivingRoomLight/toggle"
    command_param = {
        "access_token": "14e22dff-7a8e-440c-84dd-6c4a103f075b"
    }
    command_header = {}


    print(command_url)
    
    command_response = requests.put(
        url=command_url, 
        params=command_param, 
        headers=command_header,
        data=({"command": "toggle"})
    )
    
class AllStuff(object):
    def on_get(self, req, resp):
    
##Handle GET requests
        resp.status = falcon.HTTP_200
        resp.body = ('Toggling All Lights')
        allofthelight_allofthelights()


class TrinStuff(object):
    def on_get(self, req, resp):
    

        resp.status = falcon.HTTP_200
        resp.body = ('Toggling Trins light')
        toggle_trin()


class CaptainStuff(object):
    def on_get(self, req, resp):
    

        resp.status = falcon.HTTP_200
        resp.body = ('Toggling Captain Light')
        toggle_captain()


class LivingRoomStuff(object):
    def on_get(self, req, resp):
    

        resp.status = falcon.HTTP_200
        resp.body = ('Toggling Living Room light ')
        toggle_lr()


class StairsStuff(object):
    def on_get(self, req, resp):
    

        resp.status = falcon.HTTP_200
        resp.body = ('Toggling Stairs Light')
        toggle_stairs()


        
app = falcon.API()

allofthelights = AllStuff()
#route and handle requests to the ‘/all’ URL path
app.add_route('/all', allofthelights)

trin = TrinStuff()
app.add_route('/trin', trin)

captain = CaptainStuff()
app.add_route('/captain', captain)


stairs = StairsStuff()
app.add_route('/stairs', stairs)


living = LivingRoomStuff()
app.add_route('/living', living)






