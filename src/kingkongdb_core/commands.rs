/**
 * @file config.rs
 * @author Krisna Pranav
 * @brief Config
 * @version 0.1
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023 Krisna Pranav, KingKongDevelopers
 * 
 */


use bson::Document;
use bson::oid::ObjectId;
use serde::{Serialize, Deseralize};
use crate::TransactionType;

#[derive(Serialize, Deseralize)]
#[serde(rename_all = "camelCase")]
pub struct FindCommandOptions {
    pub session_id: Option<ObjectId>,
}

#[derive(Serialize, Deseralize)]
pub struct FindCommand {
    pub ns: String,
    pub multi: bool,
    pub filter: Option<Document>,
    pub options: Option<FindCommandOptions>
}

#[derive(Serialize, Deseralize)]
#[serde(rename_all = "camelCase")]
pub struct InsertCommandOptions {
    pub session_id: Option<ObjectId>,
}

#[derive(Serialize, Deseralize)]
pub struct InsertCommand {
    pub ns: String,
    pub documents: Vec<Document>,
    pub options: Option<InsertCommandOptions>,
}

#[derive(Serialize, Deseralize)]
#[serde(rename_all = "camelCase")]
pub struct UpdateCommandOptions {
    pub session_id: Option<ObjectId>
}

#[derive(Serialize, Deseralize)]
pub struct UpdateCommand {
    pub ns: String,
    pub filter: Document,
    pub update: Document,
    pub multi: bool,
    pub options: Option<UpdateCommandOptions>,
}

#[derive(Serialize, Deseralize)]
#[serde(rename_all = "camelCase")]
pub struct DeleteCommandOptions {
    pub session_id: Option<ObjectId>,
}

#[derive(Serialize, Deseralize)]
pub struct DeleteCommand {
    pub ns: String,
    pub filter: Document,
    pub multi: bool,
    pub options: Option<DeleteCommandOptions>
}

#[derive(Serialize, Deseralize)]
#[serde(tag = "command")]
pub enum CommandMessage {
    Find(FindCommand),
    Insert(InsertCommand),
    Update(UpdateCommand),
    Delete(DeleteCommand),
}
