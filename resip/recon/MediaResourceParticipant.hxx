#if !defined(MediaResourceParticipant_hxx)
#define MediaResourceParticipant_hxx

#include <resip/stack/Uri.hxx>

#include "ConversationManager.hxx"
#include "Participant.hxx"

// sipX includes
#include "os/OsNotification.h"
#include "mp/MpPlayerListener.h"

class MpStreamPlayer;
class MpPlayerEvent;

namespace useragent
{
class ConversationManager;

/**
  This class represents a media resource participant.
  A media resource participant is a representation of the a playing
  audio file or tone.

  Author: Scott Godin (sgodin AT SipSpectrum DOT com)
*/

class MediaResourceParticipant : public Participant, public OsNotification, public MpPlayerListener
{
public:  
   MediaResourceParticipant(ConversationManager::ParticipantHandle partHandle,
      ConversationManager& conversationManager,
      resip::Uri& mediaUrl);  
   virtual ~MediaResourceParticipant();

   virtual void startPlay();
   virtual int getConnectionPortOnBridge();
   virtual void destroyParticipant();

   // For PlayTone and PlayAudio callbacks
   virtual OsStatus signal(const int eventData);

   // For Stream Player callbacks
   virtual void playerRealized(MpPlayerEvent& event);
   virtual void playerPrefetched(MpPlayerEvent& event);
   virtual void playerPlaying(MpPlayerEvent& event);
   virtual void playerPaused(MpPlayerEvent& event);
   virtual void playerStopped(MpPlayerEvent& event);
   virtual void playerFailed(MpPlayerEvent& event);

protected:       

private:
   resip::Uri mMediaUrl;
   typedef enum
   {
      Invalid,
      Tone,
      File,
      Cache,
      Http,
      Https
   } ResourceType;
   ResourceType mResourceType;
   MpStreamPlayer* mStreamPlayer;

   // Play settings
   bool mLocalOnly;
   bool mRemoteOnly;
   bool mRepeat;
   bool mPrefetch;
   unsigned int mDurationMs;

   bool mPlaying;
   bool mDestroying;
};

}

#endif


/* ====================================================================

 Original contribution Copyright (C) 2008 Plantronics, Inc.
 Provided under the terms of the Vovida Software License, Version 2.0.

 The Vovida Software License, Version 2.0 
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:
 
 1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
 
 2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in
    the documentation and/or other materials provided with the
    distribution. 
 
 THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED
 WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND
 NON-INFRINGEMENT ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT
 OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT DAMAGES
 IN EXCESS OF $1,000, NOR FOR ANY INDIRECT, INCIDENTAL, SPECIAL,
 EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 DAMAGE.

 ==================================================================== */
