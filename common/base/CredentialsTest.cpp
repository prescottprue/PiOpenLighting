/*
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * CredentialsTest.cpp
 * Test the credentials functions.
 * Copyright (C) 2012 Simon Newton
 */

#include <cppunit/extensions/HelperMacros.h>

#include "ola/base/Credentials.h"
#include "ola/Logging.h"
#include "ola/testing/TestUtils.h"

using ola::GetEGID;
using ola::GetEUID;
using ola::GetGID;
using ola::GetGroupGID;
using ola::GetGroupName;
using ola::GetPasswdName;
using ola::GetPasswdUID;
using ola::GetUID;
using ola::GroupEntry;
using ola::PasswdEntry;
using ola::SetGID;
using ola::SetUID;

class CredentialsTest: public CppUnit::TestFixture {
  public:
    CPPUNIT_TEST_SUITE(CredentialsTest);
    CPPUNIT_TEST(testGetUIDs);
    CPPUNIT_TEST(testGetGIDs);
    CPPUNIT_TEST(testSetUID);
    CPPUNIT_TEST(testSetGID);
    CPPUNIT_TEST(testGetPasswd);
    CPPUNIT_TEST(testGetGroup);
    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp() {
      ola::InitLogging(ola::OLA_LOG_INFO, ola::OLA_LOG_STDERR);
    }
    void testGetUIDs();
    void testGetGIDs();
    void testSetUID();
    void testSetGID();
    void testGetPasswd();
    void testGetGroup();
};


CPPUNIT_TEST_SUITE_REGISTRATION(CredentialsTest);


/**
 * Check we're not running as root.
 */
void CredentialsTest::testGetUIDs() {
  uid_t uid = GetUID();
  OLA_ASSERT_TRUE_MSG(uid, "Don't run the tests as root!");

  uid_t euid = GetEUID();
  OLA_ASSERT_TRUE_MSG(euid, "Don't run the tests as suid root!");
}


/**
 * Check we're not running as root.
 */
void CredentialsTest::testGetGIDs() {
  gid_t gid = GetGID();
  OLA_ASSERT_TRUE_MSG(gid, "Don't run the tests as root!");

  gid_t egid = GetEGID();
  OLA_ASSERT_TRUE_MSG(egid, "Don't run the tests as sgid root!");
}


/**
 * Check SetUID as much as we can.
 */
void CredentialsTest::testSetUID() {
  uid_t euid = GetEUID();

  if (euid) {
    OLA_ASSERT_TRUE(SetUID(euid));
    OLA_ASSERT_FALSE(SetUID(0));
    OLA_ASSERT_FALSE(SetUID(euid + 1));
  }
}


/**
 * Check SetGID as much as we can.
 */
void CredentialsTest::testSetGID() {
  gid_t egid = GetEGID();

  if (egid) {
    OLA_ASSERT_TRUE(SetGID(egid));
    OLA_ASSERT_FALSE(SetGID(0));
    OLA_ASSERT_FALSE(SetGID(egid + 1));
  }
}


/**
 * Check the GetPasswd functions work.
 */
void CredentialsTest::testGetPasswd() {
  uid_t uid = GetUID();

  PasswdEntry passwd_entry;
  OLA_ASSERT_TRUE(GetPasswdUID(uid, &passwd_entry));
  // at the very least we shoud have a name
  OLA_ASSERT_FALSE(passwd_entry.pw_name.empty());
  OLA_ASSERT_EQ(uid, passwd_entry.pw_uid);

  // now fetch by name and check it's the same
  // this could fail. if the accounts were really messed up
  PasswdEntry passwd_entry2;
  OLA_ASSERT_TRUE(GetPasswdName(passwd_entry.pw_name, &passwd_entry2));
  OLA_ASSERT_EQ(uid, passwd_entry2.pw_uid);
}


/**
 * Check the GetGroup functions work.
 */
void CredentialsTest::testGetGroup() {
  gid_t gid = GetGID();

  GroupEntry group_entry;
  // not all systems will be configured with a group entry so this isn't a
  // failure.
  bool ok = GetGroupGID(gid, &group_entry);
  if (ok) {
    // at the very least we shoud have a name
    OLA_ASSERT_FALSE(group_entry.gr_name.empty());
    OLA_ASSERT_EQ(gid, group_entry.gr_gid);

    // now fetch by name and check it's the same
    // this could fail. if the accounts were really messed up
    GroupEntry group_entry2;
    OLA_ASSERT_TRUE(GetGroupName(group_entry.gr_name, &group_entry2));
    OLA_ASSERT_EQ(gid, group_entry2.gr_gid);
  }
}
