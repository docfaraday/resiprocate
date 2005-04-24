#if !defined(REPRO_USERABSTRACTDB_HXX)
#define REPRO_USERABSTRACTDB_HXX


#include "resiprocate/os/Data.hxx"
#include "resiprocate/os/Fifo.hxx"
#include "resiprocate/Message.hxx"

namespace resip
{
  class TransactionUser;
}

namespace repro
{

typedef resip::Fifo<resip::Message> MessageFifo;

class UserAbstractDb
{
   public:
      typedef resip::Data Key;
      
      UserAbstractDb();
      
      virtual ~UserAbstractDb();
      
      void requestUserAuthInfo( const resip::Data& user, 
                                const resip::Data& realm,
                                const resip::Data& transactionId,
                                resip::TransactionUser& transactionUser) const;

      resip::Data getUserAuthInfo( const Key& key ) const;
      resip::Data getUserAuthInfo( const resip::Data& user,
                                   const resip::Data& realm ) const;
      
      void addUser( const resip::Data& user, 
                    const resip::Data& domain, 
                    const resip::Data& realm, 
                    const resip::Data& password, 
                    const resip::Data& fullName,
                    const resip::Data& emailAddress  );
      
      void removeUser( const resip::Data& user,
                       const resip::Data& realm );
      
      void removeUser( const Key& key );
      
      //Data getForward( Data& key);
      //void requestForwardAuth( user, realm );
      //void setForward( Data& key, Data& forwardAddress );

      Key getFirstKey();// return empty if no more
      Key getNextKey(); // return empty if no more 
      
   protected:
      Key buildKey( const resip::Data& user, 
                    const resip::Data& realm) const;
      
      class UserRecord
      {
         public:
            short version;
            resip::Data user;
            resip::Data domain;
            resip::Data realm;
            resip::Data passwordHash;
            resip::Data name;
            resip::Data email;
            resip::Data forwardAddress;
      };
      
      resip::Data encodeUserRecord( const UserRecord& userRec ) const;
      UserRecord decodeUserRecord( const resip::Data& data ) const;

      // Db manipulation routines
      virtual void dbWriteRecord( const Key& key, const resip::Data& data ) =0;
      virtual bool dbReadRecord( const Key& key, resip::Data& data ) const =0 ; // return false if not found
      virtual void dbRemoveRecord( const Key& key ) = 0 ;

      virtual Key dbFirstKey()=0;// return empty if no more
      virtual Key dbNextKey(bool first=false)=0; // return empty if no more 
};

 }
#endif  

/* ====================================================================
 * The Vovida Software License, Version 1.0 
 * 
 * Copyright (c) 2000 Vovida Networks, Inc.  All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 
 * 3. The names "VOCAL", "Vovida Open Communication Application Library",
 *    and "Vovida Open Communication Application Library (VOCAL)" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact vocal@vovida.org.
 *
 * 4. Products derived from this software may not be called "VOCAL", nor
 *    may "VOCAL" appear in their name, without prior written
 *    permission of Vovida Networks, Inc.
 * 
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND
 * NON-INFRINGEMENT ARE DISCLAIMED.  IN NO EVENT SHALL VOVIDA
 * NETWORKS, INC. OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT DAMAGES
 * IN EXCESS OF $1,000, NOR FOR ANY INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 * 
 * ====================================================================
 * 
 * This software consists of voluntary contributions made by Vovida
 * Networks, Inc. and many individuals on behalf of Vovida Networks,
 * Inc.  For more information on Vovida Networks, Inc., please see
 * <http://www.vovida.org/>.
 *
 */
