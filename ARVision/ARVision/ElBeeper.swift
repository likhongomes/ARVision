//
//  ElBeeper.swift
//  ARVision
//
//  Created by Ian Applebaum on 9/8/18.
//  Copyright © 2018 PennAppsXVIII. All rights reserved.
//

import Foundation
import AVFoundation
var audioPlayer : AVAudioPlayer!
var selectedSoundFileName : String = "aaahhh"
var n : Int = 0
class beeper{
    func playSound() {
        
        let soundURL = Bundle.main.url(forResource: selectedSoundFileName, withExtension: "mp3")
        do {
            audioPlayer = try AVAudioPlayer(contentsOf: soundURL!)
        } catch {
            print(error)
        }
        audioPlayer.play()
    }
//    func dewit(){
//        playSound()
//        
////        let when = DispatchTime.now() + 1
////        DispatchQueue.main.asyncAfter(deadline: when) {
////            selectedSoundFileName = playArray[1]
////            playSound()
////            let nextWhen = DispatchTime.now() + 1
////            DispatchQueue.main.asyncAfter(deadline: nextWhen) {
////                selectedSoundFileName = playArray[2]
////                playSound()
//            }
        }
//    }
//    
//    
//}
