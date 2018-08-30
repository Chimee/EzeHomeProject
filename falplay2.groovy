/**
 *  Falplay2
 *
 *  Copyright 2018 Chimee Eze
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
 *  in compliance with the License. You may obtain a copy of the License at:
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software distributed under the License is distributed
 *  on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License
 *  for the specific language governing permissions and limitations under the License.
 *
 */
definition(
    name: "Falplay2",
    namespace: "Eze Home",
    author: "Chimee Eze",
    description: "Testing Api Stuff",
    category: "My Apps",
    iconUrl: "https://s3.amazonaws.com/smartapp-icons/Convenience/Cat-Convenience.png",
    iconX2Url: "https://s3.amazonaws.com/smartapp-icons/Convenience/Cat-Convenience@2x.png",
    iconX3Url: "https://s3.amazonaws.com/smartapp-icons/Convenience/Cat-Convenience@2x.png",
    oauth: [displayName: "Falplay2 ", displayLink: "http://localhost:4567"])



preferences {
  section ("Allow external service to control these things...") {
    input "switches", "capability.switch", multiple: true, required: true
  }
}

mappings {
  path("/switches") {
    action: [
      GET: "listSwitches"
    ]
  }
  path("/switches/:command") {
    action: [
      PUT: "updateSwitches"
    ]
  }
  path("/switches/:sname/:command") {
  	action: [
    	PUT:"updateSwitch",
        POST: "updateSwitch"
    ]
    }
  }

// get list off all available devices 
def listSwitches() {

    def resp = []
    switches.each {
        resp << [displayNameLabel: it.displayName, name: it.name, value: it.currentValue("switch")]
    }
    return resp
}

void updateSwitches() {
    // use the built-in request object to get the command parameter
    def command = params.command
   
    
    


    // execute on/off command on all switches or toggle current state
    
    switch(command) {
        case "on":
            switches.on()
            break
        case "off":
            switches.off()
            break
        case "toggle":
        	switches.toggle()
            break
        default:
            httpError(400, "$Not all switches support specified command")
    }

}




void updateSwitch() {
    
    def command = params.command
    def sname = params.sname


	
    log.info "Request to update $sname with command $command"
    
	def theSwitch = switches.find { it.displayName == "${sname}" }
    log.debug "Current Switch: ${theSwitch}"
    def switchCurrent = theSwitch.currentValue("switch")
    log.debug "Current value: ${switchCurrent}"



    switch(command) {
        case "on":
            theSwitch.on()
            break
        case "off":
            theSwitch.off()
            break
        case "toggle":
        	if(switchCurrent == "on")
            	{theSwitch.off()}
            else
            	{theSwitch.on()}
            break
        default:
            httpError(400, "The switch specified does not support command $command")
    }

}




def installed() {}

def updated() {}