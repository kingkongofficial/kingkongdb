/**
 * @file errors.rs
 * @author Krisna Pranav
 * @brief Errors
 * @version 0.1
 * @date 2023-05-04
 * 
 * @copyright Copyright (c) 2023 Krisna Pranav, KingKongDevelopers
 * 
 */

use std::io;
use std::fmt;
use std::string::FromUtf8Error;
use std::sync::PoisonError;
use bson::Document;
use bson::ser::Error as BsonErr;
use thiserror::Error;