pub struct ConfigBuilder {
    inner: Config,
}

impl ConfigBuilder {
    pub fn new() -> ConfigBuilder {
        ConfigBuilder {
            inner: Config::default(),
        }
    }

    pub fn get_init_block_count(&self) -> u64 {
        self.inner.init_block_count
    }

    pub fn set_init_block_count(&mut self, v: u64) -> &mut Self {
        self.inner.init_block_count = v;
        self
    }

    pub fn take(self) -> Config {
        self.inner
    }
}

pub struct Config {
    pub init_block_count: u64,
    pub journal_full_size: u64,
    pub lsm_page_size: u32,
    pub lsm_block_size: u32,
    pub sync_log_count: u32,
}

#[cfg(not(target_arch = "wasm32"))]
const SYNC_LOG_COUNT: u64 = 1000;

#[cfg(target_arch = "wasm32")]
const SYNC_LOG_COUNT: u64 = 200;

impl Default for Config {
    fn default() -> Self {
        Config {
            init_block_count: 16,
            journal_full_size: 1000,
            lsm_page_size: 4096,
            lsm_block_size: 4 * 1024 * 1024,
            sync_log_count: SYNC_LOG_COUNT,
        }
    }
}