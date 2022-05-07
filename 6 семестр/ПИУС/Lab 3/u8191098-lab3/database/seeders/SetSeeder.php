<?php

namespace Database\Seeders;

use Illuminate\Database\Seeder;
use App\Models\Set;

class SetSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
        Set::factory()->count(500)->create();
    }
}
